#include "Scene_Option.h"

#include "CAnchor.h"
#include "CControllerFactory.h"
#include "CImageManager.h"
#include "CProgressData.h"

Scene_Option::Scene_Option(SceneManager* ScnMng)
    : Scene_Abstract(ScnMng),
      scaling_option_{"640x480", "1280x960"},
      sound_option_{"PCM音源", "FM音源"},
      menu_selector_(2, 0) {
  input_ = CControllerFactory::GetIns().GetController();
  text_[0] = CTextDrawer::Text("OPTION", CVector(320 - 3.0 * 30, 32.0), 0xFFFFFF,
                              0xFF0000, 2);
  text_[1] =
      CTextDrawer::Text("", CVector(320 - 36 * 7, 180), 0xFFFFFF, 0xCFCF00, 1);
  text_[1].text_ = std::string("画面解像度:") +
                 scaling_option_[CProgressData::GetIns().GetWindowX2()];
  text_[2] =
      CTextDrawer::Text("", CVector(320 - 36 * 7, 250), 0xFFFFFF, 0x00CF00, 1);
  text_[2].text_ = std::string("BGM音源:") +
                 sound_option_[CProgressData::GetIns().GetFMorPCM()];
  text_[3] =
      CTextDrawer::Text("設定は次のゲーム起動から適用されます。",
                        CVector(320 - 10 * 12, 320), 0xFFFFFF, 0x00CFCF, 0);
}

void Scene_Option::Update() {
  if (input_.lock()->Start() == 1) {
    CProgressData::GetIns().Save();
    scene_manager_->PopScene();
    return;
  }
  if (input_.lock()->Up() == 1) menu_selector_.Prev();
  if (input_.lock()->Down() == 1) menu_selector_.Next();
  switch (menu_selector_.Get()) {
    case 0:
      if (input_.lock()->Right() == 1 || input_.lock()->Left() == 1) {
        CProgressData::GetIns().SetWindowX2(
            (CProgressData::GetIns().GetWindowX2() + 1) % 2);
      }
      text_[1].text_ = std::string("画面解像度:") +
                     scaling_option_[CProgressData::GetIns().GetWindowX2()];
      break;
    case 1:
      if (input_.lock()->Right() == 1 || input_.lock()->Left() == 1) {
        CProgressData::GetIns().SetFMorPCM(
            (CProgressData::GetIns().GetFMorPCM() + 1) % 2);
      }
      text_[2].text_ = std::string("BGM音源:") +
                     sound_option_[CProgressData::GetIns().GetFMorPCM()];
      break;
  }
}

void Scene_Option::Render() const {
  CAnchor::GetIns().EnableAbsolute();
  CImageManager::GetIns()
      .Find("system_curtain")
      ->Draw(0 - (12 - cnt_) / 12.0 * 320, 0.0, 100, 0);
  CImageManager::GetIns()
      .Find("system_curtain")
      ->Draw(320 + (12 - cnt_) / 12.0 * 320, 0.0, 100, 1);
  for (int i = 0; i < 4; i++) {
    CTextDrawer::GetIns().Register(text_[i]);
  }
  CImageManager::GetIns().Find("icon_return")->Draw(0, 0, 101);
  CImageManager::GetIns()
      .Find("enemy_marker")
      ->Draw((int)text_[menu_selector_.Get() + 1].position_.x - 32,
             (int)text_[menu_selector_.Get() + 1].position_.y, 101, 0);
  CAnchor::GetIns().DisableAbsolute();
}