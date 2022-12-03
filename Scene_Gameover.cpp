#include "Scene_Gameover.h"
#include "CProgressData.h"
#include "CControllerFactory.h"
#include "CImageManager.h"
#include "CAnchor.h"

Scene_Gameover::Scene_Gameover(SceneManager* ScnMng):Scene_Abstract(ScnMng), cnt(0)
{
	input = CControllerFactory::getIns().getController();
	text[0] = CTextDrawer::Text("GAME OVER ...", CVector(320 - 6.5 * 30, 32.0), 0xFFFFFF, 0xFF0000, 2);
	text[1] = CTextDrawer::Text("", CVector(320 - 36*7, 180), 0xFFFFFF, 0xCFCF00, 1);
	text[1].text = std::string("コインを") + std::to_string(CProgressData::getIns().getEarnedMoney()) + std::string("枚獲得しました。");
	text[2] = CTextDrawer::Text("SPACEキーを押すとタイトル画面に戻ります。", CVector(320 - 10*12, 320), 0xFFFFFF, 0x00CFCF, 0);
}

void Scene_Gameover::Update()
{
	if (input.lock()->Select() == 1)scn_mng->ChangeScene(Constant::SCENE_ID::SCENE_TITLE, true);
	cnt = min(++cnt, 12);
}

void Scene_Gameover::Render() const
{
	CAnchor::getIns().enableAbsolute();
	CImageManager::getIns().find("system_curtain")->Draw(0 - (12 - cnt) / 12.0 * 320, 0, 100, 0);
	CImageManager::getIns().find("system_curtain")->Draw(320 + (12 - cnt) / 12.0 * 320, 0, 100, 1);
	for (int i = 0; i < 3; i++) {
		CTextDrawer::getIns().Register(text[i]);
	}
	CAnchor::getIns().disableAbsolute();
}
