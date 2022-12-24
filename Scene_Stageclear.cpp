#include "Scene_Stageclear.h"
#include "CControllerFactory.h"
#include "CProgressData.h"
#include "CImageManager.h"
#include "CAnchor.h"
#include "CPassiveSkill.h"

Scene_Stageclear::Scene_Stageclear(SceneManager* ScnMng) :Scene_Abstract(ScnMng), cnt(0), cur(0)
{
	input = CControllerFactory::getIns().getController();
	text[0] = CTextDrawer::Text("STAGE CLEAR!!", CVector(320 - 6.5 * 30, 32.0), 0xFFFFFF, 0xFF0000, 2);
	text[1] = CTextDrawer::Text("", CVector(320 - 36 * 7, 140), 0xFFFFFF, 0xCFCF00, 1);
	text[1].text = std::string("コインを") + std::to_string(CProgressData::getIns().getEarnedMoney()) + std::string("枚獲得しました。");
	text[2] = CTextDrawer::Text("", CVector(320 - 36 * 8, 180), 0xFFFFFF, 0xCFCF00, 1);
	text[2].text = std::string("クリア報酬で") + std::to_string(CProgressData::getIns().getStageMoney()) + std::string("枚獲得しました。");
	text[3] = CTextDrawer::Text("SPACEキーを押すとスキルを取得して次のステージに進みます。", CVector(320 - 14 * 12, 350), 0xFFFFFF, 0x00CFCF, 0);
	text[4] = CTextDrawer::Text("ESCキーを押すとアップグレードが出来ます。", CVector(320 - 10 * 12, 380), 0xFFFFFF, 0xCFCF00, 0);
	skillList = CPassiveSkill::getIns().getRandomList();
	CProgressData::getIns().save();
}

void Scene_Stageclear::Update()
{
	if (input.lock()->Right() == 1) {
		cur = (cur + 1) % skillList.size();
	}
	if (input.lock()->Left() == 1) {
		cur = (cur + skillList.size() - 1) % skillList.size();
	}
	if (input.lock()->Select() == 1) {
		CPassiveSkill::getIns().add(skillList[cur]);
		CProgressData::getIns().nextCurrentStage();
		scn_mng->ChangeScene(Constant::SCENE_ID::SCENE_MAIN, true);
		return;
	}
	/*if (input.lock()->Start() == 1) {
		scn_mng->ChangeScene(Constant::SCENE_ID::SCENE_UPGRADE, false);
		return;
	}*/
	cnt = min(++cnt, 12);
}

void Scene_Stageclear::Render() const
{
	CAnchor::getIns().enableAbsolute();
	CImageManager::getIns().find("system_curtain")->Draw(0 - (12 - cnt) / 12.0 * 320, 0, 100, 0);
	CImageManager::getIns().find("system_curtain")->Draw(320 + (12 - cnt) / 12.0 * 320, 0, 100, 1);
	for (int i = 0; i < skillList.size(); i++) {
		CImageManager::getIns().find("icon_passiveskill")->Draw(320 - 64 * 1.5 + 64 * i, 240, 101, skillList[i]);
	}
	CImageManager::getIns().find("system_costume_frame")->DrawRota(320 - 64 * 1.5 + 64 * cur + 16, 240 + 16, 0, 1, 102);
	CTextDrawer::getIns().Register(CPassiveSkill::getIns().getText(skillList[cur]));
	for (int i = 0; i < 4; i++) {
		CTextDrawer::getIns().Register(text[i]);
	}
	CAnchor::getIns().disableAbsolute();
}
