#include "Scene_Stageclear.h"

#include "CAnchor.h"
#include "CControllerFactory.h"
#include "CImageManager.h"
#include "CPassiveSkill.h"
#include "CProgressData.h"

Scene_Stageclear::Scene_Stageclear(SceneManager* ScnMng)
    : Scene_Abstract(ScnMng), cnt_(0), cur_(0) {
  input_ = CControllerFactory::GetIns().GetController();
  text_[0] = CTextDrawer::Text("STAGE CLEAR!!", CVector(320 - 6.5 * 30, 32.0),
                              0xFFFFFF, 0xFF0000, 2);
  text_[1] =
      CTextDrawer::Text("", CVector(320 - 36 * 7, 140), 0xFFFFFF, 0xCFCF00, 1);
  text_[1].text_ = std::string("コインを") +
                 std::to_string(CProgressData::GetIns().GetEarnedMoney()) +
                 std::string("枚獲得しました。");
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
  skill_list_ = CPassiveSkill::GetIns().GetRandomList();
  CProgressData::GetIns().Save();
}

void Scene_Stageclear::Update() {
  if (input_.lock()->Right() == 1) {
    cur_ = (cur_ + 1) % skill_list_.size();
  }
  if (input_.lock()->Left() == 1) {
    cur_ = (cur_ + (int)skill_list_.size() - 1) % (int)skill_list_.size();
  }
  if (input_.lock()->Select() == 1) {
    CPassiveSkill::GetIns().Add(skill_list_[cur_]);
    CProgressData::GetIns().NextCurrentStage();
    scene_manager_->ChangeScene(Constant::SceneID::kSceneMain, true);
    return;
  }
  /*if (input_.lock()->Start() == 1) {
          scene_manager_->ChangeScene(Constant::SCENE_ID::SCENE_UPGRADE, false);
          return;
  }*/
  cnt_ = min(++cnt_, 12);
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
  CImageManager::GetIns()
      .Find("system_costume_frame")
      ->DrawRota(int(320 - 64 * 1.5 + 64 * cur_ + 16), 240 + 16, 0.0f, 1.0f, 102);
  CTextDrawer::GetIns().Register(
      CPassiveSkill::GetIns().GetText(skill_list_[cur_]));
  for (int i = 0; i < 4; i++) {
    CTextDrawer::GetIns().Register(text_[i]);
  }
  CAnchor::GetIns().DisableAbsolute();
}
