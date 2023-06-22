#include "Scene_Gameclear.h"

#include "Graphic/CAnchor.h"
#include "Input/CControllerFactory.h"
#include "Graphic/Image/CImageManager.h"
#include "Calc/CProgressData.h"
#include "Sound/CSoundManager.h"
#include "Calc/CStatus.h"

Scene_Gameclear::Scene_Gameclear(SceneManager* ScnMng)
    : Scene_Abstract(ScnMng), cnt_(0) {
  input_ = CControllerFactory::GetIns().GetController();
  text_[0] = CTextDrawer::Text("CONGRATULATION!!", CVector(320 - 8 * 30, 32),
                              0xFFFFFF, 0xFF0000, 2);
  text_[1] =
      CTextDrawer::Text("最終ステージをクリアしました！",
                        CVector(320 - 36 * 8, 180), 0xFFFFFF, 0xCFCF00, 1);
  text_[2] =
      CTextDrawer::Text("プレイしてくれてありがとう！",
                        CVector(320 - 36 * 8, 216), 0xFFFFFF, 0xCFCF00, 1);
  text_[3] =
      CTextDrawer::Text("SPACEキーを押すとタイトル画面に戻ります。",
                        CVector(320 - 10 * 12, 320), 0xFFFFFF, 0x00CFCF, 0);
  CProgressData::GetIns().Save();
}

void Scene_Gameclear::Update() {
  if (input_.lock()->Select() == 1) {
    CProgressData::GetIns().NextCurrentStage();
    scene_manager_->ChangeScene(Constant::SceneID::kSceneTitle, true);
    return;
  }
  cnt_ = min(++cnt_, 12);
}

void Scene_Gameclear::Render() const {
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
  CAnchor::GetIns().DisableAbsolute();
}
