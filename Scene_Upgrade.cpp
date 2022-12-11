#include "Scene_Upgrade.h"
#include "CControllerFactory.h"
#include "CProgressData.h"
#include "CImageManager.h"
#include "CAnchor.h"
#include "CStatus.h"
#include "CSoundManager.h"
#include <cassert>

Scene_Upgrade::Scene_Upgrade(SceneManager* ScnMng) :Scene_Abstract(ScnMng), hasEnoughMoney(true), cnt(0), now(CProgressData::getIns().getPlayerLevel()), next(CProgressData::getIns().getPlayerLevel()+1)
{
	input = CControllerFactory::getIns().getController();
	text[0] = CTextDrawer::Text("アップグレード", CVector(320 - 3.5 * 60, 32.0), 0xFFFFFF, 0x7F7F00, 2);
	text[1] = CTextDrawer::Text("所持コイン", CVector(320 - 36 * 5, 120), 0xFFFFFF, 0xCFCF00, 1);
	text[2] = CTextDrawer::Text("必要コイン", CVector(320 - 36 * 5, 160), 0xFFFFFF, 0xCFCF00, 1);
	text[3] = CTextDrawer::Text("現在のステータス", CVector(320 - 200, 240), 0xFFFFFF, 0xCFCF00, 0);
	text[4] = CTextDrawer::Text("強化後ステータス", CVector(320 - 200, 270), 0xFFFFFF, 0xCFCF00, 0);
	text[5] = CTextDrawer::Text("SPACEキーを押すとコインを消費して強化します。", CVector(320 - 10 * 12, 320), 0xFFFFFF, 0x00CFCF, 0);
	text[6] = CTextDrawer::Text("コインが足りません！", CVector(320 - 5 * 36, 360), 0xFFFFFF, 0xFF0000, 1);
	CSoundManager::getIns().find("money")->SetVolume(0.5);
	CSoundManager::getIns().find("player_hit")->SetVolume(0.5);
}

void Scene_Upgrade::Update()
{
	now = CStatus(CProgressData::getIns().getPlayerLevel());
	next = CStatus(CProgressData::getIns().getPlayerLevel() + 1);
	text[1].text = std::string("所持コイン：") + std::to_string(CProgressData::getIns().getMoney());
	text[2].text = std::string("必要コイン：") + std::to_string(CStatus::getMoneyToUpgrade(CProgressData::getIns().getPlayerLevel()));
	text[3].text = std::string("現在のステータス→") + std::string("HP:") + floating_to_string(now.MaxHP)
		+ std::string(" ATK:") + floating_to_string(now.ATK);
	text[4].text = std::string("強化後ステータス→") + std::string("HP:") + floating_to_string(next.MaxHP)
		+ std::string(" ATK:") + floating_to_string(next.ATK);
	if (input.lock()->Select() == 1) {
		if (CProgressData::getIns().getMoney() >= CStatus::getMoneyToUpgrade(CProgressData::getIns().getPlayerLevel())) {
			CProgressData::getIns().upgrade(CStatus::getMoneyToUpgrade(CProgressData::getIns().getPlayerLevel()));
			hasEnoughMoney = true;
			CSoundManager::getIns().find("money")->Play(CSound::PLAYTYPE::PT_BACK);
		}
		else {
			CSoundManager::getIns().find("player_hit")->Play(CSound::PLAYTYPE::PT_BACK);
			hasEnoughMoney = false;
		}
	}
	if (input.lock()->Start() == 1) {
		CProgressData::getIns().save();
		scn_mng->ChangeScene(Constant::SCENE_ID::SCENE_TITLE, true);
		return;
	}
}

void Scene_Upgrade::Render() const
{
	assert(text[0].position.y < 40.0);
	CAnchor::getIns().enableAbsolute();
	CImageManager::getIns().find("system_curtain")->Draw(0, 0, 100, 0);
	CImageManager::getIns().find("system_curtain")->Draw(320, 0, 100, 1);
	for (int i = 0; i < 6; i++) {
		CTextDrawer::getIns().Register(text[i]);
	}
	if (!hasEnoughMoney)CTextDrawer::getIns().Register(text[6]);
	CImageManager::getIns().find("icon_return")->Draw(0, 0, 101);
	CAnchor::getIns().disableAbsolute();
}
