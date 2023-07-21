#include "Scene_Gallery.h"

#include "Calc/CPassiveSkill.h"
#include "Calc/CProgressData.h"
#include "Calc/CStatus.h"
#include "Data/CDataLoader.h"
#include "Graphic/CAnchor.h"
#include "Graphic/Image/CImageManager.h"
#include "Input/CControllerFactory.h"
#include "Sound/CSoundManager.h"

Scene_Gallery::Scene_Gallery(SceneManager* ScnMng)
    : Scene_Abstract(ScnMng), menu_selector_(3, 0), attr_{0.0} {
  input_ = CControllerFactory::GetIns().GetController();
  input_.lock()->SetMouseInvisible();
  auto d = CDataLoader::GetIns().Get("main")->GetChild("enemy");
  if (d == nullptr) {
    MessageBox(NULL, "error at enemy params", "CDataNode", MB_OK);
    abort();
  }
  menu_selector_ = CMenuSelector(d->GetChildNum(), 0);
  enemy_name_ = CTextDrawer::Text("", CVector(120, 120), 0xFFFFFF, 0x000000, 1);
  enemy_detail_ =
      CTextDrawer::Text("", CVector(60, 320), 0xFFFFFF, 0x000000, 0);
  enemy_name_.text_ =
      d->GetChild(menu_selector_.Get()).second->GetChild("name")->GetString();
  enemy_detail_.text_ =
      d->GetChild(menu_selector_.Get()).second->GetChild("detail")->GetString();
  enemy_gid_ =
      d->GetChild(menu_selector_.Get()).second->GetChild("graph")->GetString();
}

void Scene_Gallery::Update() {
  auto updateEnemyInfo = [&]() {
    auto d = CDataLoader::GetIns().Get("main")->GetChild("enemy");
    if (d == nullptr) {
      MessageBox(NULL, "error at enemy params", "CDataNode", MB_OK);
      abort();
    }
    enemy_name_.text_ =
        d->GetChild(menu_selector_.Get()).second->GetChild("name")->GetString();
    enemy_detail_.text_ = d->GetChild(menu_selector_.Get())
                              .second->GetChild("detail")
                              ->GetString();
    enemy_gid_ = d->GetChild(menu_selector_.Get())
                     .second->GetChild("graph")
                     ->GetString();
    CAttribute attribute_(0.0);
    attribute_.Load(d->GetChild(menu_selector_.Get()).second->GetChild("atrd"));
    attr_[0] = attribute_.none_;
    attr_[1] = attribute_.fire_;
    attr_[2] = attribute_.aqua_;
    attr_[3] = attribute_.thunder_;
    attr_[4] = attribute_.flower_;
    attr_[5] = attribute_.ice_;
    attr_[6] = attribute_.wind_;
  };
  if (input_.lock()->Right() == 1) {
    CSoundManager::GetIns().Find("cursor")->Play(CSound::PlayType::kBack);
    menu_selector_.Next();
    updateEnemyInfo();
  }
  if (input_.lock()->Left() == 1) {
    CSoundManager::GetIns().Find("cursor")->Play(CSound::PlayType::kBack);
    menu_selector_.Prev();
    updateEnemyInfo();
  }

  if (input_.lock()->Start() == 1) {
    scene_manager_->ChangeScene(Constant::SceneID::kSceneTitle, true);
    return;
  }
}

void Scene_Gallery::Render() const {
  CAnchor::GetIns().EnableAbsolute();
  CImageManager::GetIns().Find("system_curtain")->Draw(0, 0, 0, 0);
  CImageManager::GetIns().Find("system_curtain")->Draw(320, 0, 0, 1);

  CImageManager::GetIns().Find("icon_return")->Draw(0, 0, 101);
  CTextDrawer::GetIns().Register(enemy_name_);
  CTextDrawer::GetIns().Register(enemy_detail_);

  CImageManager::GetIns()
      .Find(enemy_gid_)
      ->DrawRotaF(Constant::kScreenW / 2, Constant::kScreenH / 2, 0.0, 1.0,
                  Constant::kPriorityEnemy, 0);

  constexpr int icon_left = 320-112;
  constexpr int icon_top = 280;
  auto drawCostumeInfo = [this](int i, double attr) {
    CImageManager::GetIns()
        .Find("icon_attribute")
        ->Draw(icon_left + 32 * i + 0, icon_top, Constant::kPriorityCurtain + 1, i);
    if (attr > 1.0) {
      CImageManager::GetIns()
          .Find("icon_weak_or_strong")
          ->Draw(icon_left + 32 * i + 16, icon_top, Constant::kPriorityCurtain + 1,
                 0);
    } else if (attr < 1.0) {
      CImageManager::GetIns()
          .Find("icon_weak_or_strong")
          ->Draw(icon_left + 32 * i + 16, icon_top, Constant::kPriorityCurtain + 1,
                 1);
    } else {
      CImageManager::GetIns()
          .Find("icon_weak_or_strong")
          ->Draw(icon_left + 32 * i + 16, icon_top, Constant::kPriorityCurtain + 1,
                 2);
    }
  };
  for (int i = 0; i < 7; i++) {
    drawCostumeInfo(i, attr_[i]);
  }

  CAnchor::GetIns().DisableAbsolute();
}