#include "CGameMediator.h"

#include "CAnchor.h"
#include "CCostumeFactory.h"
#include "CEffectParent.h"
#include "CEffect_Bright.h"
#include "CEnemyFactory.h"
#include "CEnemySpawner.h"
#include "CFieldParent.h"
#include "CImageManager.h"
#include "CMover.h"
#include "CMoverParent.h"
#include "CMover_Player.h"
#include "CPowerParent.h"
#include "CProgressData.h"
#include "CSoundManager.h"

void CGameMediator::ProcessEnemySpawner() {
  for (auto i = enemy_spawner_.begin(); i != enemy_spawner_.end();) {
    int r = (*i)->Update();
    if (r == 1) {
      i = enemy_spawner_.erase(i);
      continue;
    }
    ++i;
  }
}

CGameMediator::CGameMediator(SceneManager* ScnMng)
    : Scene_Abstract(ScnMng),
      is_pause_(true),
      is_retire_(false),
      pause_guage_(0),
      cnt_(0),
      is_initialized_(false),
      costume_selecter_cnt_(12),
      is_costume_selecter_end_(false),
      now_level_of_stage_(CProgressData::GetIns().GetCurrentStage() * 3),
      number_drawer_() {
  input_ = CControllerFactory::GetIns().GetController();
  retire_text_[0] =
      CTextDrawer::Text("本当にリタイアしますか？", CVector(320 - 6 * 36, 32),
                        0xFFFFFF, 0x000000, 1);
  retire_text_[1] =
      CTextDrawer::Text("SPACEキーを押すとタイトル画面に戻ります。",
                        CVector(320 - 10 * 12, 320), 0xFFFFFF, 0x00CFCF, 0);
  wave_number_ = CTextDrawer::Text(
      std::string("WAVE:") +
          std::to_string(CProgressData::GetIns().GetCurrentStage() + 1),
      CVector(320 + 88, 8), 0xFFFFFF, 0x000000, 1);
  skill_list_ = CPassiveSkill::GetIns().GetGotSkillList();
  skill_level_list_ = CPassiveSkill::GetIns().GetGotSkillLevelList();
}

CGameMediator::~CGameMediator() {}

void CGameMediator::CreateParts() {
  mover_parent_ = std::make_unique<CMoverParent>(this);
  field_parent_ = std::make_unique<CFieldParent>(
      this, CProgressData::GetIns().GetMapFilepath());
  power_parent_ = std::make_unique<CPowerParent>(this);

  CVector playerPos;
  field_parent_->readStageData(enemy_spawner_, now_level_of_stage_, playerPos);
  CCostumeFactory CCF;
  CCF.GetMinMaxFriction(min_fric_, max_fric_);
  CCF.GetMinMaxWaterRes(min_water_res_, max_water_res_);
  CCF.GetMinMaxAirRes(min_air_res_, max_air_res_);
  CCF.GetMinMaxMass(min_mass_, max_mass_);
  CCF.GetMinMaxVelocity(min_velocity_, max_velocity_);
  CCF.GetMinMaxAccel(min_accel_, max_accel_);
  costume_now_focus_ = std::make_unique<CCostumeBase*>(CCF.Create("C_Uniform"));
  RegisterMover(player_ = std::make_shared<CMover_Player>(
                    playerPos, CProgressData::GetIns().GetPlayerLevel(),
                    CCF.Create("C_Uniform")));
  CSoundManager::GetIns().Find("bgm")->SetVolume(0.8);
  CSoundManager::GetIns().Find("bgm")->Play(CSound::kLoop);
  CEffectParent::Reset();
  CEffect_Bright::GetIns().Inactivate();
  is_initialized_ = true;
}

void CGameMediator::RegisterMover(std::shared_ptr<CMover> m) {
  m->SetMediator(this);
  mover_parent_->RegisterMover(m);
}

void CGameMediator::RegisterPower(std::shared_ptr<CPower> p) {
  power_parent_->Add(p);
}

void CGameMediator::ApplyForceToMover(CMover* m) {
  power_parent_->ApplyForceToMover(m);
  field_parent_->ApplyForceToMover(m);
}

bool CGameMediator::HitToMover(CMover* m) {
  return field_parent_->HitToMover(m);
}

CVector CGameMediator::GetPlayerPosition() {
  std::weak_ptr<CMover> p =
      mover_parent_->GetMover(CMover::MoverID::kPlayer, 0);
  if (!p.lock()) return CVector(false);
  return CVector(p.lock()->GetPosition());
}

std::list<CVector> CGameMediator::GetRoute(CVector start, CVector goal,
                                           CAttribute attrDEF, int distance) {
  return field_parent_->GetRoute(start, goal, attrDEF, distance);
}

std::vector<CVector> CGameMediator::GetTargetByDistance(CVector start,
                                                        int distance) {
  return field_parent_->GetTargetByDistance(start, distance);
}

std::weak_ptr<CMover> CGameMediator::GetNearestMover(int ID, CVector p) {
  int i = 0;
  auto cur = mover_parent_->GetMover(ID, i);
  if (!cur.lock()) return std::weak_ptr<CMover>();
  double dist = (p - cur.lock()->GetPosition()).GetLength2();
  i++;
  while (1) {
    auto next = mover_parent_->GetMover(ID, i);
    if (!next.lock()) break;
    if (dist > (p - next.lock()->GetPosition()).GetLength2()) {
      dist = (p - next.lock()->GetPosition()).GetLength2();
      cur = next;
    }
    i++;
  }
  return cur;
}

void CGameMediator::GetMoney(int value) { reserve_money_ += value; }

void CGameMediator::Update() {
  if (!is_initialized_) return;
  cnt_++;
  if (is_retire_) {
    UpdateRetireMenu();
    return;
  }
  if (is_pause_) {
    UpdateDresschangeMenu();
    return;
  }
#ifdef _DEBUG
  if (input_.lock()->Start() == 1) {
    CEffect_Bright::GetIns().Inactivate();
    scene_manager_->ChangeScene(Constant::SceneID::kSceneEditor, true);
    return;
  }
#endif
  if (player_->GetHP() < 0) {
    CSoundManager::GetIns().Find("bgm")->Stop();
    CSoundManager::GetIns().Find("player_dead")->Play(CSound::PlayType::kBack);
    CProgressData::GetIns().Lose(reserve_money_);
    CEffect_Bright::GetIns().Inactivate();
    scene_manager_->ChangeScene(Constant::SceneID::kSceneGameover, false);
    return;
  }
  if (mover_parent_->GetCountByCategory(CMover::MoverID::kEnemy) == 0 &&
      enemy_spawner_.empty()) {
    CSoundManager::GetIns().Find("bgm")->Stop();
    CSoundManager::GetIns().Find("success")->Play(CSound::PlayType::kBack);
    CProgressData::GetIns().Win(reserve_money_);
    CEffect_Bright::GetIns().Inactivate();
    if (CProgressData::GetIns().GetCurrentStage() ==
        CProgressData::GetIns().GetMaxStage() - 1) {
      if (CProgressData::GetIns().GetEndless()) {
        scene_manager_->ChangeScene(Constant::SceneID::kSceneStageclear, false);
      } else
        scene_manager_->ChangeScene(Constant::SceneID::kSceneGameclear, false);
    } else {
      scene_manager_->ChangeScene(Constant::SceneID::kSceneStageclear, false);
    }
    return;
  }
  CEnemyFactory CEF;
  ++pause_guage_;
  pause_guage_ = min(pause_guage_, Constant::kMaxPause);
  if (input_.lock()->Select() == 1) {
    if (pause_guage_ == Constant::kMaxPause) {
      is_pause_ = true;
      costume_selecter_cnt_ = 0;
      CEffect_Bright::GetIns().Inactivate();
    }
  }
  ProcessEnemySpawner();
  if (mover_parent_->GetCountByCategory(CMover::MoverID::kEnemy) == 0) {
    ProcessEnemySpawner();
  }
  CEffect_Bright::GetIns().Clear();
  power_parent_->Update();
  mover_parent_->Update();
  field_parent_->Update();
  CEffectParent::Update();
}

void CGameMediator::Render() const {
  field_parent_->Render();
  mover_parent_->Render();
  power_parent_->Render();
  CEffectParent::Render();
  CAnchor::GetIns().EnableAbsolute();
  CImageManager::GetIns()
      .Find("system_dress_guage")
      ->DrawRectwithBlend(
          240, 480 - 32, 160, 32, 0xFFFFFF, CImageManager::BlendMode::kNone, 0,
          Constant::kPriorityUI + 3, (input_.lock()->Select() > 0) ? 1 : 0);
  if (pause_guage_ == Constant::kMaxPause)
    CImageManager::GetIns()
        .Find("system_dress_guage")
        ->DrawRectwithBlend(240, 480 - 32, 160, 32, 0xFFFFFF,
                            CImageManager::BlendMode::kNone, 0,
                            Constant::kPriorityUI + 4, 2);
  CImageManager::GetIns()
      .Find("system_dress_guage")
      ->DrawRectwithBlend(
          240, 480 - 32, (int)(160 * ((double)pause_guage_ / Constant::kMaxPause)), 32,
          HSV2RGB((float)(cnt_ % 60) / 60, 1.0, 1.0),
          CImageManager::BlendMode::kSub, 0x7F, Constant::kPriorityUI + 5,
          (input_.lock()->Select() > 0) ? 1 : 0);
  number_drawer_.Draw(16, 56, reserve_money_, 0, 3, Constant::kPriorityNumber);
  CImageManager::GetIns()
      .Find("system_passive_frame")
      ->Draw(320 + 24, 8, Constant::kPriorityNumber + 1);
  for (int i = 0; i < 5; i++) {
    if (i < skill_list_.size()) {
      CImageManager::GetIns()
          .Find("icon_passiveskill")
          ->Draw(321 + 24 + 32 * i, 8 + 1, Constant::kPriorityNumber,
                 skill_list_[i]);
      CImageManager::GetIns()
          .Find("icon_passive_progress")
          ->Draw(321 + 24 + 32 * i, 8 + 32 + 1, Constant::kPriorityNumber,
                 skill_level_list_[i]);
    } else
      CImageManager::GetIns()
          .Find("icon_passive_covered")
          ->Draw(321 + 24 + 32 * i, 8 + 1, Constant::kPriorityNumber);
  }
  CAnchor::GetIns().DisableAbsolute();

  if (is_retire_) {
    RenderRetireMenu();
    return;
  }
  if (is_pause_) {
    RenderDresschangeMenu();
    return;
  }

#ifdef _DEBUG
  printfDx("Money:%d\nGraphHandle:%d\n", reserve_money_, GetGraphNum());
#endif
}

void CGameMediator::UpdateDresschangeMenu() {
  static CCostumeFactory CCF;
  static int currentCostumeIndex = 0;
  costume_now_focus_ =
      std::make_unique<CCostumeBase*>(CCF.Create(currentCostumeIndex));
  costume_selecter_cnt_ =
      min(is_costume_selecter_end_ ? --costume_selecter_cnt_
                                   : ++costume_selecter_cnt_,
          12);
  if (is_costume_selecter_end_) {
    if (costume_selecter_cnt_ != 0) return;
    costume_selecter_cnt_ = 0;
    is_pause_ = false;
    is_costume_selecter_end_ = false;
    return;
  }
  if (input_.lock()->Select() == 1) {
    is_costume_selecter_end_ = true;
    pause_guage_ = 0;
    player_->ChangeCostume(CCF.Create(currentCostumeIndex));
    CEffect_Bright::GetIns().Activate();
    return;
  }
  if (input_.lock()->Start() == 1) {
    is_retire_ = true;
    return;
  }
  if (input_.lock()->Right() == 1) {
    currentCostumeIndex += 1;
    currentCostumeIndex %= CCF.GetSize();
  }
  if (input_.lock()->Left() == 1) {
    currentCostumeIndex += CCF.GetSize() - 1;
    currentCostumeIndex %= CCF.GetSize();
  }
}

void CGameMediator::RenderDresschangeMenu() const {
  CAnchor::GetIns().EnableAbsolute();
  CTextDrawer::GetIns().Register(wave_number_);
  CImageManager::GetIns()
      .Find("system_curtain")
      ->Draw(0 - (12 - costume_selecter_cnt_) / 12.0 * 320, 0.0,
             Constant::kPriorityCurtain, 0);
  CImageManager::GetIns()
      .Find("system_curtain")
      ->Draw(320 + (12 - costume_selecter_cnt_) / 12.0 * 320, 0.0,
             Constant::kPriorityCurtain, 1);
  CImageManager::GetIns()
      .Find("system_costume_frame")
      ->DrawRota(160, 64, 0.0f, 1.0f, Constant::kPriorityCurtain + 2);
  CImageManager::GetIns()
      .Find((*costume_now_focus_)->gid_)
      ->DrawRota(160, 64, 0.0f, 1.0f, Constant::kPriorityCurtain + 1, 4);

  auto drawStatusGuage = [this](int i, double value, double next_value,
                                double max, double min) {
    CImageManager::GetIns()
        .Find("system_status_guage")
        ->Draw(360, 80 + i * 64, Constant::kPriorityCurtain + 3, 1);
    CImageManager::GetIns()
        .Find("system_status_guage")
        ->Draw(360, 80 + i * 64, Constant::kPriorityCurtain + 1, 3);
    CImageManager::GetIns()
        .Find("system_status_next_now")
        ->Draw(344, 80 + i * 64, Constant::kPriorityCurtain + 1, 1);
    CImageManager::GetIns()
        .Find("system_status_guage")
        ->Draw(360, 96 + i * 64, Constant::kPriorityCurtain + 3, 1);
    CImageManager::GetIns()
        .Find("system_status_guage")
        ->Draw(360, 96 + i * 64, Constant::kPriorityCurtain + 1, 3);
    CImageManager::GetIns()
        .Find("system_status_next_now")
        ->Draw(344, 96 + i * 64, Constant::kPriorityCurtain + 1, 0);
    CImageManager::GetIns()
        .Find("system_status_guage")
        ->Draw(360, 64 + i * 64, Constant::kPriorityCurtain + 3, 0);
    CImageManager::GetIns()
        .Find("system_status_name")
        ->Draw(360 + 80, 64 + i * 64, Constant::kPriorityCurtain + 3, i);

    CImageManager::GetIns()
        .Find("system_status_guage")
        ->DrawRectwithBlend(
            360, 80 + i * 64,
            int(240 *
                min(1.0, max(0.02, (value - min) / max(0.0001, max - min)))),
            16, 0xFFFFFF, CImageManager::BlendMode::kNone, 0,
            Constant::kPriorityCurtain + 2, 2);
    CImageManager::GetIns()
        .Find("system_status_guage")
        ->DrawRectwithBlend(
            360, 96 + i * 64,
            int(240 * min(1.0, max(0.02, (next_value - min) /
                                             max(0.0001, max - min)))),
            16, 0xFFFFFF, CImageManager::BlendMode::kNone, 0,
            Constant::kPriorityCurtain + 2, 2);
  };
  double values[6] = {
      player_->costume_->cofs_.FrictionCF, player_->costume_->cofs_.WaterResCF,
      player_->costume_->cofs_.AirResCF,   player_->costume_->mass_,
      player_->costume_->max_speed_,       player_->costume_->accel_};
  double next_values[6] = {(*costume_now_focus_)->cofs_.FrictionCF,
                           (*costume_now_focus_)->cofs_.WaterResCF,
                           (*costume_now_focus_)->cofs_.AirResCF,
                           (*costume_now_focus_)->mass_,
                           (*costume_now_focus_)->max_speed_,
                           (*costume_now_focus_)->accel_};
  double maxs[6] = {max_fric_, max_water_res_, max_air_res_,
                    max_mass_, max_velocity_,  max_accel_};
  double mins[6] = {min_fric_, min_water_res_, min_air_res_,
                    min_mass_, min_velocity_,  min_accel_};
  for (int i = 0; i < 6; i++) {
    drawStatusGuage(i, values[i], next_values[i], maxs[i], mins[i]);
  }
  const int icon_left = 48;
  auto drawCostumeInfo = [this](int i, double attr) {
    CImageManager::GetIns()
        .Find("icon_attribute")
        ->Draw(icon_left + 32 * i + 0, 96, Constant::kPriorityCurtain + 1, i);
    if (attr > 1.0) {
      CImageManager::GetIns()
          .Find("icon_weak_or_strong")
          ->Draw(icon_left + 32 * i + 16, 96, Constant::kPriorityCurtain + 1,
                 0);
    } else if (attr < 1.0) {
      CImageManager::GetIns()
          .Find("icon_weak_or_strong")
          ->Draw(icon_left + 32 * i + 16, 96, Constant::kPriorityCurtain + 1,
                 1);
    } else {
      CImageManager::GetIns()
          .Find("icon_weak_or_strong")
          ->Draw(icon_left + 32 * i + 16, 96, Constant::kPriorityCurtain + 1,
                 2);
    }
  };
  double attrs[7] = {(*costume_now_focus_)->attribute_def_.none_,
                     (*costume_now_focus_)->attribute_def_.fire_,
                     (*costume_now_focus_)->attribute_def_.aqua_,
                     (*costume_now_focus_)->attribute_def_.thunder_,
                     (*costume_now_focus_)->attribute_def_.flower_,
                     (*costume_now_focus_)->attribute_def_.ice_,
                     (*costume_now_focus_)->attribute_def_.wind_};
  for (int i = 0; i < 7; i++) {
    drawCostumeInfo(i, attrs[i]);
  }
  CImageManager::GetIns()
      .Find("system_dress_guage")
      ->DrawRectwithBlend(240, 480 - 32, 160, 32, 0xFFFFFF,
                          CImageManager::BlendMode::kNone, 0,
                          Constant::kPriorityCurtain + 1,
                          (input_.lock()->Select() > 0) ? 1 : 0);
  CImageManager::GetIns()
      .Find("system_dress_guage")
      ->DrawRectwithBlend(240, 480 - 32, 160, 32, 0xFFFFFF,
                          CImageManager::BlendMode::kNone, 0,
                          Constant::kPriorityCurtain + 2, 2);
  CImageManager::GetIns()
      .Find("system_dress_guage")
      ->DrawRectwithBlend(
          240, 480 - 32, 160, 32, HSV2RGB((float)(cnt_ % 60) / 60, 1.0, 1.0),
          CImageManager::BlendMode::kSub, 0x7F, Constant::kPriorityCurtain + 3,
          (input_.lock()->Select() > 0) ? 1 : 0);
  CImageManager::GetIns()
      .Find("icon_return")
      ->Draw(0, 0, Constant::kPriorityCurtain + 1);
  CAnchor::GetIns().DisableAbsolute();
  CTextDrawer::GetIns().RegisterForCostumeDetail(
      (*costume_now_focus_)->detail_);
}

void CGameMediator::UpdateRetireMenu() {
  if (input_.lock()->Start() == 1) {
    is_retire_ = false;
    return;
  }
  if (input_.lock()->Select() == 1) {
    CSoundManager::GetIns().Find("bgm")->Stop();
    scene_manager_->ChangeScene(Constant::SceneID::kSceneTitle, true);
    return;
  }
}

void CGameMediator::RenderRetireMenu() const {
  CAnchor::GetIns().EnableAbsolute();
  CImageManager::GetIns()
      .Find("system_curtain")
      ->Draw(0, 0, Constant::kPriorityCurtain, 0);
  CImageManager::GetIns()
      .Find("system_curtain")
      ->Draw(320, 0, Constant::kPriorityCurtain, 1);
  CImageManager::GetIns()
      .Find("icon_return")
      ->Draw(0, 0, Constant::kPriorityCurtain + 1);
  for (auto& i : retire_text_) {
    CTextDrawer::GetIns().Register(i);
  }
  CAnchor::GetIns().DisableAbsolute();
}
