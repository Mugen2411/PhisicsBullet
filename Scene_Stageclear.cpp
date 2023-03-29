#include "Scene_Stageclear.h"

#include <format>

#include "CAnchor.h"
#include "CControllerFactory.h"
#include "CImageManager.h"
#include "CPassiveSkill.h"
#include "CProgressData.h"

Scene_Stageclear::Scene_Stageclear(SceneManager* ScnMng)
    : Scene_Abstract(ScnMng), cnt_(0), cnt_color_(0), cur_(0) {
  input_ = CControllerFactory::GetIns().GetController();
  text_[0] = CTextDrawer::Text("STAGE CLEAR!!", CVector(320 - 6.5 * 30, 32.0),
                               0xFFFFFF, 0xFF0000, 2);
  text_[1] =
      CTextDrawer::Text("", CVector(320 - 36 * 8, 140), 0xFFFFFF, 0xCFCF00, 1);
  if (log10(CProgressData::GetIns().GetEarnedMoney()) <= 8) {
    text_[1].text_ =
        std::string("コインを") +
        std::format("{:.0f}", (CProgressData::GetIns().GetEarnedMoney())) +
        std::string("枚獲得しました。");
  } else {
    text_[1].text_ =
        std::string("コインを") +
        std::format("{:4.3e}", (CProgressData::GetIns().GetEarnedMoney())) +
        std::string("枚獲得しました。");
  }
  
  text_[2] =
      CTextDrawer::Text("", CVector(320 - 36 * 8, 180), 0xFFFFFF, 0xCFCF00, 1);
  text_[2].text_ = std::string("クリア報酬で") +
                   std::to_string(CProgressData::GetIns().GetStageMoney()) +
                   std::string("枚獲得しました。");
  text_[3] = CTextDrawer::Text(
      "SPACEキーを押すとスキルを取得して次のステージに進みます。",
      CVector(320 - 14 * 12, 350), 0xFFFFFF, 0x00CFCF, 0);
  text_[4] =
      CTextDrawer::Text("ESCキーを押すとアップグレードが出来ます。",
                        CVector(320 - 10 * 12, 380), 0xFFFFFF, 0xCFCF00, 0);
  text_[5] =
      CTextDrawer::Text("スキル フルチャージ！", CVector(320.0 - 8 * 21, 280.0),
                        0xFFFFFF, 0x000000, 1);
  skill_list_ = CPassiveSkill::GetIns().GetRandomList();
  if (skill_list_.empty())
    text_[3].text_ = "SPACEキーを押すと次のステージに進みます。";
  CProgressData::GetIns().Save();
}

void Scene_Stageclear::Update() {
  if (!skill_list_.empty()) {
    if (input_.lock()->Right() == 1) {
      cur_ = (cur_ + 1) % skill_list_.size();
    }
    if (input_.lock()->Left() == 1) {
      cur_ = (cur_ + (int)skill_list_.size() - 1) % (int)skill_list_.size();
    }
  } else
    text_[5].edge_color_ = HSV2RGB((float)(cnt_color_) / 60.0f, 1.0, 1.0);

  if (input_.lock()->Select() == 1) {
    if (!skill_list_.empty()) CPassiveSkill::GetIns().Add(skill_list_[cur_]);
    CProgressData::GetIns().NextCurrentStage();
    scene_manager_->ChangeScene(Constant::SceneID::kSceneMain, true);
    return;
  }
  /*if (input_.lock()->Start() == 1) {
          scene_manager_->ChangeScene(Constant::SCENE_ID::SCENE_UPGRADE, false);
          return;
  }*/
  cnt_ = min(++cnt_, 12);
  cnt_color_ = (++cnt_color_) % 60;
}

void Scene_Stageclear::Render() const {
  CAnchor::GetIns().EnableAbsolute();
  CImageManager::GetIns()
      .Find("system_curtain")
      ->Draw(0 - (12 - cnt_) / 12.0 * 320, 0.0, 100, 0);
  CImageManager::GetIns()
      .Find("system_curtain")
      ->Draw(320 + (12 - cnt_) / 12.0 * 320, 0.0, 100, 1);
  for (int i = 0; i < skill_list_.size(); i++) {
    CImageManager::GetIns()
        .Find("icon_passiveskill")
        ->Draw(320 - 64 * 1.5 + 64 * i, 240.0, 101, skill_list_[i]);
  }
  if (!skill_list_.empty())
    CImageManager::GetIns()
        .Find("system_costume_frame")
        ->DrawRota(int(320 - 64 * 1.5 + 64 * cur_ + 16), 240 + 16, 0.0f, 1.0f,
                   102);
  if (!skill_list_.empty())
    CTextDrawer::GetIns().Register(
        CPassiveSkill::GetIns().GetText(skill_list_[cur_]));
  else
    CTextDrawer::GetIns().Register(text_[5]);

  for (int i = 0; i < 4; i++) {
    CTextDrawer::GetIns().Register(text_[i]);
  }
  CAnchor::GetIns().DisableAbsolute();
}
