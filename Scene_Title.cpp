#include "Scene_Title.h"

#include "CAnchor.h"
#include "CControllerFactory.h"
#include "CImageManager.h"
#include "CPassiveSkill.h"
#include "CProgressData.h"
#include "CSoundManager.h"

Scene_Title::Scene_Title(SceneManager* ScnMng)
    : Scene_Abstract(ScnMng), menu_selector_(6, 0), current_stage_(0) {
  input_ = CControllerFactory::GetIns().GetController();
  menu_text_[0] =
      CTextDrawer::Text("Start", CVector(340, 200), 0xFFFFFF, 0x007F7F, 1);
  menu_text_[1] =
      CTextDrawer::Text("Endless", CVector(340, 240), 0xFFFFFF, 0x000000, 1);
  menu_text_[2] =
      CTextDrawer::Text("Upgrade", CVector(340, 280), 0xFFFFFF, 0x7F7F00, 1);
  menu_text_[3] =
      CTextDrawer::Text("Option", CVector(340, 320), 0xFFFFFF, 0x7F7F7F, 1);
  menu_text_[4] =
      CTextDrawer::Text("Manual", CVector(340, 360), 0xFFFFFF, 0x007F00, 1);
  menu_text_[5] =
      CTextDrawer::Text("Quit", CVector(340, 400), 0xFFFFFF, 0x7F0000, 1);
  under_text_[0] = CTextDrawer::Text(
      "ADキーでステージを選択しSPACEキーでゲームを開始します。",
      CVector(36, 480 - 22), 0xFFFFFF, 0x000000, 0);
  under_text_[1] =
      CTextDrawer::Text("エンドレスモードでゲームを開始します。",
                        CVector(36, 480 - 22), 0xFFFFFF, 0x000000, 0);
  under_text_[2] =
      CTextDrawer::Text("ゲーム内通貨を使用して自機のレベルを上げます。",
                        CVector(36, 480 - 22), 0xFFFFFF, 0x000000, 0);
  under_text_[3] = CTextDrawer::Text(
      "各種設定を変更します。", CVector(36, 480 - 22), 0xFFFFFF, 0x000000, 0);
  under_text_[4] =
      CTextDrawer::Text("操作方法やルールの説明を見ます。(メモ帳を開きます)",
                        CVector(36, 480 - 22), 0xFFFFFF, 0x000000, 0);
  under_text_[5] = CTextDrawer::Text(
      "ゲームを終了します。", CVector(36, 480 - 22), 0xFFFFFF, 0x000000, 0);
  title_text_ = CTextDrawer::Text("MAKEOVER trial", CVector(320 - 72 * 3.0, 32.0),
                                0xFFFFFF, 0x0000FF, 2);
  CProgressData::GetIns().Load();
  input_.lock()->SetMouseInvisible();
}

void Scene_Title::Update() {
#ifdef _DEBUG
  if (input_.lock()->Start() == 1) {
    scene_manager_->ChangeScene(Constant::SceneID::kSceneEditor, true);
    return;
  }
#endif
  if (input_.lock()->Down() == 1) {
    CSoundManager::GetIns().Find("cursor")->Play(CSound::PlayType::kBack);
    menu_selector_.Next();
  }
  if (input_.lock()->Up() == 1) {
    CSoundManager::GetIns().Find("cursor")->Play(CSound::PlayType::kBack);
    menu_selector_.Prev();
  }
#ifdef _DEBUG
  if (menu_selector_.Get() == 0) {
    if (input_.lock()->Right() == 1)
      current_stage_ =
          (current_stage_ + 1) % (CProgressData::GetIns().GetMaxStage());
    if (input_.lock()->Left() == 1)
      current_stage_ =
          (current_stage_ + CProgressData::GetIns().GetMaxStage() - 1) %
          (CProgressData::GetIns().GetMaxStage());
  }
#else
  if (menu_selector_.Get() == 0 || menu_selector_.Get() == 1) {
    if (input_.lock()->Right() == 1)
      current_stage_ =
          (current_stage_ + 1) % (CProgressData::GetIns().GetLastStage() + 1);
    if (input_.lock()->Left() == 1)
      current_stage_ = (current_stage_ + CProgressData::GetIns().GetLastStage()) %
                     (CProgressData::GetIns().GetLastStage() + 1);
  }
#endif
  menu_text_[0].text_ = std::string("Start→") + std::to_string(current_stage_ + 1);
  // menu_text_[1].text_ = std::string("Endless Start→") +
  // std::to_string(current_stage_ + 1);
  if (input_.lock()->Select() == 1) {
    CSoundManager::GetIns().Find("success")->Play(CSound::PlayType::kBack);
    switch (menu_selector_.Get()) {
      case 0:
        CPassiveSkill::GetIns().Reset();
        CProgressData::GetIns().SetCurrentStage(current_stage_);
        CProgressData::GetIns().SetEndless(false);
        scene_manager_->ChangeScene(Constant::SceneID::kSceneMain, true);
        break;
      case 1:
        CPassiveSkill::GetIns().Reset();
        CProgressData::GetIns().SetCurrentStage(0);
        CProgressData::GetIns().SetEndless(true);
        scene_manager_->ChangeScene(Constant::SceneID::kSceneMain, true);
        break;
      case 2:
        scene_manager_->ChangeScene(Constant::SceneID::kSceneUpgrade, false);
        break;
      case 3:
        scene_manager_->ChangeScene(Constant::SceneID::kSceneOption, false);
        break;
      case 4:
        ShellExecute(NULL, "open", "readme.txt", NULL, NULL, SW_SHOW);
        break;
      case 5:
        scene_manager_->ChangeScene(Constant::SceneID::kSceneQuit, true);
        break;
    }
    return;
  }
  for (int i = 0; i < 6; i++) {
    if (menu_selector_.Get() == i)
      menu_text_[i].position_.x = 400;
    else
      menu_text_[i].position_.x = 420;
  }
}

void Scene_Title::Render() const {
  CAnchor::GetIns().EnableAbsolute();
  CImageManager::GetIns().Find("system_curtain")->Draw(0, 0, 0, 0);
  CImageManager::GetIns().Find("system_curtain")->Draw(320, 0, 0, 1);
  CImageManager::GetIns()
      .Find("title_face")
      ->DrawRota(216, Constant::kScreenH - 256, 0, 1, 1, 0);
  for (int i = 0; i < 6; i++) {
    CTextDrawer::GetIns().Register(menu_text_[i]);
  }
  CTextDrawer::GetIns().Register(title_text_);
  CTextDrawer::GetIns().Register(under_text_[menu_selector_.Get()]);
  CAnchor::GetIns().DisableAbsolute();
}