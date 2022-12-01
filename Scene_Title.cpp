#include "Scene_Title.h"
#include "CControllerFactory.h"
#include "CProgressData.h"
#include "CImageManager.h"

Scene_Title::Scene_Title(SceneManager* ScnMng) :Scene_Abstract(ScnMng), CMS(3, 0), currentStage(0) {
	input = CControllerFactory::getIns().getController();
	menuText[0] = CTextDrawer::Text("Start→stage:", CVector(320, 280), 0xFFFFFF, 0x007F7F, 1);
	menuText[1] = CTextDrawer::Text("Upgrade", CVector(320, 320), 0xFFFFFF, 0x7F7F00, 1);
	menuText[2] = CTextDrawer::Text("Quit", CVector(320, 360), 0xFFFFFF, 0x7F0000, 1);
	titleText = CTextDrawer::Text("タイトル未定！", CVector(320-72*3.5, 32.0), 0xFFFFFF, 0x0000FF, 2);
	CProgressData::getIns().load();
}

void Scene_Title::Update() {
	if (input.lock()->Down() == 1)CMS.next();
	if (input.lock()->Up() == 1)CMS.prev();
	if (CMS.get() == 0) {
		if (input.lock()->Right() == 1)currentStage = (currentStage + 1) % CProgressData::getIns().getLastStage();
		if (input.lock()->Left() == 1)currentStage = (currentStage + (CProgressData::getIns().getLastStage() - 1)) % CProgressData::getIns().getLastStage();
	}
	menuText[0].text = std::string("Start→stage:") + std::to_string(currentStage);
	if (input.lock()->Select() == 1) {
		switch (CMS.get()) {
		case 0:
			CProgressData::getIns().setCurrentStage(currentStage);
			scn_mng->ChangeScene(Constant::SCENE_ID::SCENE_MAIN, true);
			break;
		case 2:
			scn_mng->ChangeScene(Constant::SCENE_ID::SCENE_QUIT, true);
		}
	}
	for (int i = 0; i < 3; i++) {
		if (CMS.get() == i)menuText[i].position.x = 300;
		else menuText[i].position.x = 320;
	}
}

void Scene_Title::Render()const {
	DrawBox(0, 0, Constant::ScreenW, Constant::ScreenH, 0x00FF00, TRUE);
	CImageManager::getIns().find("title_face")->DrawRota(216, Constant::ScreenH - 256, 0, 1, 0, 0);
	for (int i = 0; i < 3; i++) {
		CTextDrawer::getIns().Register(menuText[i]);
	}
	CTextDrawer::getIns().Register(titleText);
}