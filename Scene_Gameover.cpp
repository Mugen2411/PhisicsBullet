#include "Scene_Gameover.h"

#include "CAnchor.h"
#include "CControllerFactory.h"
#include "CImageManager.h"
#include "CProgressData.h"

Scene_Gameover::Scene_Gameover(SceneManager* ScnMng)
    : Scene_Abstract(ScnMng), cnt_(0) {
  input_ = CControllerFactory::GetIns().GetController();
  text_[0] = CTextDrawer::Text("GAME OVER ...", CVector(320 - 6.5 * 30, 32.0),
                              0xFFFFFF, 0xFF0000, 2);
  text_[1] =
      CTextDrawer::Text("", CVector(320 - 36 * 7, 180), 0xFFFFFF, 0xCFCF00, 1);
  text_[1].text_ = std::string("コインを") +
                 std::to_string(CProgressData::GetIns().GetEarnedMoney()) +
                 std::string("枚獲得しました。");
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
