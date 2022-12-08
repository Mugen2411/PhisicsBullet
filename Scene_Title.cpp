#include "Scene_Title.h"
#include "CControllerFactory.h"
#include "CProgressData.h"
#include "CImageManager.h"
#include "CAnchor.h"
#include "CSoundManager.h"

Scene_Title::Scene_Title(SceneManager* ScnMng) :Scene_Abstract(ScnMng), CMS(3, 0), currentStage(0) {
	input = CControllerFactory::getIns().getController();
	menuText[0] = CTextDrawer::Text("Start→stage:", CVector(340, 280), 0xFFFFFF, 0x007F7F, 1);
	menuText[1] = CTextDrawer::Text("Upgrade", CVector(340, 320), 0xFFFFFF, 0x7F7F00, 1);
	menuText[2] = CTextDrawer::Text("Quit", CVector(340, 360), 0xFFFFFF, 0x7F0000, 1);
	underText[0] = CTextDrawer::Text("SPACEキーでゲームを開始します。", CVector(36, 480 - 22), 0xFFFFFF, 0x000000, 0);
	underText[1] = CTextDrawer::Text("ゲーム内通貨を使用して自機のレベルを上げます。", CVector(36, 480 - 22), 0xFFFFFF, 0x000000, 0);
	underText[2] = CTextDrawer::Text("ゲームを終了します。", CVector(36, 480 - 22), 0xFFFFFF, 0x000000, 0);
	titleText = CTextDrawer::Text("タイトル未定！", CVector(320 - 72 * 3.5, 32.0), 0xFFFFFF, 0x0000FF, 2);
	CProgressData::getIns().load();
	CSoundManager::getIns().find("success")->SetVolume(0.5);
	CSoundManager::getIns().find("cursor")->SetVolume(0.5);
}

void Scene_Title::Update() {
#ifdef _DEBUG
	if (input.lock()->Start() == 1) {
		scn_mng->ChangeScene(Constant::SCENE_ID::SCENE_EDITOR, true);
		return;
	}
#endif
	if (input.lock()->Down() == 1) {
		CSoundManager::getIns().find("cursor")->Play(CSound::PLAYTYPE::PT_BACK);
		CMS.next();
	}
	if (input.lock()->Up() == 1) {
		CSoundManager::getIns().find("cursor")->Play(CSound::PLAYTYPE::PT_BACK);
		CMS.prev();
	}
	if (CMS.get() == 0) {
		if (input.lock()->Right() == 1)currentStage = (currentStage + 1) % (CProgressData::getIns().getLastStage() + 1);
		if (input.lock()->Left() == 1)currentStage = (currentStage + CProgressData::getIns().getLastStage()) % (CProgressData::getIns().getLastStage() + 1);
	}
	menuText[0].text = std::string("Start");
	if (input.lock()->Select() == 1) {
		CSoundManager::getIns().find("success")->Play(CSound::PLAYTYPE::PT_BACK);
		switch (CMS.get()) {
		case 0:
			CProgressData::getIns().setCurrentStage(currentStage);
			scn_mng->ChangeScene(Constant::SCENE_ID::SCENE_MAIN, true);
			break;
		case 1:
			scn_mng->ChangeScene(Constant::SCENE_ID::SCENE_UPGRADE, true);
			break;
		case 2:
			scn_mng->ChangeScene(Constant::SCENE_ID::SCENE_QUIT, true);
			break;
		}
		return;
	}
	for (int i = 0; i < 3; i++) {
		if (CMS.get() == i)menuText[i].position.x = 320;
		else menuText[i].position.x = 340;
	}
}

void Scene_Title::Render()const {
	CAnchor::getIns().enableAbsolute();
	CImageManager::getIns().find("system_curtain")->Draw(0, 0, 0, 0);
	CImageManager::getIns().find("system_curtain")->Draw(320, 0, 0, 1);
	CImageManager::getIns().find("title_face")->DrawRota(216, Constant::ScreenH - 256, 0, 1, 1, 0);
	for (int i = 0; i < 3; i++) {
		CTextDrawer::getIns().Register(menuText[i]);
	}
	CTextDrawer::getIns().Register(titleText);
	CTextDrawer::getIns().Register(underText[CMS.get()]);
	CAnchor::getIns().disableAbsolute();
}