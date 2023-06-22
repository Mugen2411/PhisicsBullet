#include "Scene_Gameover.h"

#include <format>

#include "Graphic/CAnchor.h"
#include "Input/CControllerFactory.h"
#include "Graphic/Image/CImageManager.h"
#include "Calc/CProgressData.h"
#include "Sound/CSoundManager.h"
#include "Calc/CStatus.h"

Scene_Gameover::Scene_Gameover(SceneManager* ScnMng)
    : Scene_Abstract(ScnMng), cnt_(0) {
  input_ = CControllerFactory::GetIns().GetController();
  text_[0] = CTextDrawer::Text("GAME OVER ...", CVector(320 - 6.5 * 30, 32.0),
                               0xFFFFFF, 0xFF0000, 2);
  text_[1] =
      CTextDrawer::Text("", CVector(320 - 36 * 8, 180), 0xFFFFFF, 0xCFCF00, 1);
  if (log10(CProgressData::GetIns().GetEarnedMoney()) <=
      Constant::kExpoBorder) {
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
      CTextDrawer::Text("SPACEキーを押すとタイトル画面に戻ります。",
                        CVector(320 - 10 * 12, 320), 0xFFFFFF, 0x00CFCF, 0);
  CProgressData::GetIns().Save();
}

void Scene_Gameover::Update() {
  if (input_.lock()->Select() == 1) {
    scene_manager_->ChangeScene(Constant::SceneID::kSceneTitle, true);
    return;
  }
  cnt_ = min(++cnt_, 12);
}

void Scene_Gameover::Render() const {
  CAnchor::GetIns().EnableAbsolute();
  CImageManager::GetIns()
      .Find("system_curtain")
      ->Draw(0 - (12 - cnt_) / 12.0 * 320, 0.0, 100, 0);
  CImageManager::GetIns()
      .Find("system_curtain")
      ->Draw(320 + (12 - cnt_) / 12.0 * 320, 0.0, 100, 1);
  for (int i = 0; i < 3; i++) {
    CTextDrawer::GetIns().Register(text_[i]);
  }
  CAnchor::GetIns().DisableAbsolute();
}
