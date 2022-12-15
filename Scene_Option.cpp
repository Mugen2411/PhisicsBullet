#include "Scene_Option.h"
#include "CControllerFactory.h"
#include "CProgressData.h"
#include "CAnchor.h"
#include "CImageManager.h"

Scene_Option::Scene_Option(SceneManager* ScnMng) :Scene_Abstract(ScnMng), scalingOption{ "640x480","1280x960"} {
	input = CControllerFactory::getIns().getController();
	text[0] = CTextDrawer::Text("OPTION", CVector(320 - 3.0 * 30, 32.0), 0xFFFFFF, 0xFF0000, 2);
	text[1] = CTextDrawer::Text("", CVector(320 - 36 * 7, 180), 0xFFFFFF, 0xCFCF00, 1);
	text[1].text = std::string("��ʉ𑜓x:") + scalingOption[CProgressData::getIns().getWindowX2()];
	text[2] = CTextDrawer::Text("�ݒ�͎��̃Q�[���N������K�p����܂��B", CVector(320 - 10 * 12, 320), 0xFFFFFF, 0x00CFCF, 0);
}

void Scene_Option::Update() {
	if (input.lock()->Start() == 1) {
		CProgressData::getIns().save();
		scn_mng->PopScene();
		return;
	}
	if (input.lock()->Right() == 1 || input.lock()->Left() == 1) {
		CProgressData::getIns().setWindowX2((CProgressData::getIns().getWindowX2() + 1)%2);
	}
	text[1].text = std::string("��ʉ𑜓x:") + scalingOption[CProgressData::getIns().getWindowX2()];
}

void Scene_Option::Render()const {
	CAnchor::getIns().enableAbsolute();
	CImageManager::getIns().find("system_curtain")->Draw(0 - (12 - cnt) / 12.0 * 320, 0, 100, 0);
	CImageManager::getIns().find("system_curtain")->Draw(320 + (12 - cnt) / 12.0 * 320, 0, 100, 1);
	for (int i = 0; i < 3; i++) {
		CTextDrawer::getIns().Register(text[i]);
	}
	CImageManager::getIns().find("icon_return")->Draw(0, 0, 101);
	CAnchor::getIns().disableAbsolute();
}