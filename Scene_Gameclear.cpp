#include "Scene_Gameclear.h"

#include "CAnchor.h"
#include "CControllerFactory.h"
#include "CImageManager.h"
#include "CProgressData.h"

Scene_Gameclear::Scene_Gameclear(SceneManager* ScnMng)
    : Scene_Abstract(ScnMng), cnt(0) {
  input = CControllerFactory::getIns().getController();
  text[0] = CTextDrawer::Text("CONGRATULATION!!", CVector(320 - 8 * 30, 32),
                              0xFFFFFF, 0xFF0000, 2);
  text[1] =
      CTextDrawer::Text("最終ステージをクリアしました！",
                        CVector(320 - 36 * 8, 180), 0xFFFFFF, 0xCFCF00, 1);
  text[2] =
      CTextDrawer::Text("プレイしてくれてありがとう！",
                        CVector(320 - 36 * 8, 216), 0xFFFFFF, 0xCFCF00, 1);
  text[3] =
      CTextDrawer::Text("SPACEキーを押すとタイトル画面に戻ります。",
                        CVector(320 - 10 * 12, 320), 0xFFFFFF, 0x00CFCF, 0);
  CProgressData::getIns().save();
}

void Scene_Gameclear::Update() {
  if (input.lock()->Select() == 1) {
    CProgressData::getIns().nextCurrentStage();
    scn_mng->ChangeScene(Constant::SCENE_ID::SCENE_TITLE, true);
    return;
  }
  cnt = min(++cnt, 12);
}

void Scene_Gameclear::Render() const {
  CAnchor::getIns().enableAbsolute();
  CImageManager::getIns()
      .find("system_curtain")
      ->Draw(0 - (12 - cnt) / 12.0 * 320, 0, 100, 0);
  CImageManager::getIns()
      .find("system_curtain")
      ->Draw(320 + (12 - cnt) / 12.0 * 320, 0, 100, 1);
  for (int i = 0; i < 4; i++) {
    CTextDrawer::getIns().Register(text[i]);
  }
  CAnchor::getIns().disableAbsolute();
}
