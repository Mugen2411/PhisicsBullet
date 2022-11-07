#include "CGameMediator.h"
#include "CMoverParent.h"
#include "CFieldParent.h"
#include "CPowerParent.h"
#include "CEffectParent.h"
#include "CMover_Player.h"
#include "CCostumeFactory.h"
#include "CEnemyFactory.h"
#include "CMover.h"
#include "CSoundManager.h"
#include "CImageManager.h"
#include "CAnchor.h"

CGameMediator::CGameMediator(SceneManager* ScnMng) :Scene_Abstract(ScnMng), isPause(false), pauseGuage(0), cnt(0)
{
	input = CControllerFactory::getIns().getController();
}

CGameMediator::~CGameMediator()
{
	OutputDebugString("CGameMediatorÇÕè¡Ç¶ÇƒÇÈ");
}

void CGameMediator::CreateParts()
{
	moverParent = std::make_shared<CMoverParent>(shared_from_this());
	fieldParent = std::make_shared<CFieldParent>(shared_from_this(), "media/map/0.map");
	powerParent = std::make_shared<CPowerParent>(shared_from_this());
	CCostumeFactory CCF;
	CCF.getMinMaxFriction(minFric, maxFric);
	CCF.getMinMaxWaterRes(minWaterRes, maxWaterRes);
	CCF.getMinMaxAirRes(minAirRes, maxAirRes);
	CCF.getMinMaxMass(minMass, maxMass);
	CCF.getMinMaxVelocity(minVelocity, maxVelocity);
	CCF.getMinMaxAccel(minAccel, maxAccel);
	costumeNowFocusOn = std::make_unique<CCostumeBase*>(CCF.create("C_Uniform"));
	RegisterMover(player = std::make_shared<CMover_Player>(CVector(8 * 32, 8 * 32), 20, CCF.create("C_Uniform")));
	CEnemyFactory CEF;
	for (int i = 0; i < 3; i++) {
		//RegisterMover(CEF.create("E_Shimaenaga", CVector(10 * 32 + 16, +48 * 32 + 16), 0));
		RegisterMover(CEF.create("E_Budcorn", CVector(1 * 32 + 16, +8 * 32 + 16), 0));
	}
	CSoundManager::getIns().find("player_hit")->SetVolume(0.5);
	CSoundManager::getIns().find("enemy_kill")->SetVolume(0.5);
	CSoundManager::getIns().find("enemy_hit")->SetVolume(0.4);
	CSoundManager::getIns().find("bgm_test")->SetVolume(0.3);
	CSoundManager::getIns().find("bgm_test")->Play(CSound::PT_LOOP);
}

void CGameMediator::RegisterMover(std::shared_ptr<CMover> m)
{
	m->setMediator(shared_from_this());
	moverParent->RegisterMover(m);
}

void CGameMediator::ApplyForceToMover(CMover* m)
{
	powerParent->ApplyForceToMover(m);
	fieldParent->ApplyForceToMover(m);
}

CVector CGameMediator::GetPlayerPosition()
{
	std::weak_ptr<CMover> p = moverParent->getMover(CMover::MOVER_ID::MV_PLAYER, 0);
	if (!p.lock())return CVector(false);
	return CVector(p.lock()->getPosition());
}

std::vector<CVector> CGameMediator::GetRoute(CVector start, CVector goal, CAttribute attrDEF)
{
	return fieldParent->getRoute(start, goal, attrDEF);
}

std::weak_ptr<CMover> CGameMediator::GetNearestMover(int ID, CVector p)
{
	int i = 0;
	auto cur = moverParent->getMover(ID, i);
	if (!cur.lock())return std::weak_ptr<CMover>();
	double dist = (p - cur.lock()->getPosition()).getLength2();
	i++;
	while (1) {
		auto next = moverParent->getMover(ID, i);
		if (!next.lock())break;
		if (dist > (p - next.lock()->getPosition()).getLength2()) {
			dist = (p - next.lock()->getPosition()).getLength2();
			cur = next;
		}
		i++;
	}
	return cur;
}

void CGameMediator::getMoney(int value)
{
	reserveMoney += value;
}

void CGameMediator::Update()
{
	if (input.lock()->Start() == 1) {
		scn_mng->ChangeScene(Constant::SCENE_ID::SCENE_EDITOR, true);
		return;
	}
	if (isPause) {
		UpdateDresschangeMenu();
		return;
	}
	CEnemyFactory CEF;
	++pauseGuage;
	pauseGuage = min(pauseGuage, Constant::MaxPause);
	if (cnt % 180 == 0)RegisterMover(CEF.create("E_Budcorn", CVector(1 * 32 + 16, +8 * 32 + 16), 0));
	if (input.lock()->A() == 1) {
		CCostumeFactory CCF;
		player->ChangeCostume(CCF.create("C_Festa"));
	}
	if (input.lock()->Select() == 1) {
		if (pauseGuage == Constant::MaxPause)isPause = true;
	}
	powerParent->Update();
	moverParent->Update();
	fieldParent->Update();
	CEffectParent::Update();
	cnt++;
}

void CGameMediator::Render() const
{
	fieldParent->Render();
	moverParent->Render();
	powerParent->Render();
	CEffectParent::Render();
	CAnchor::getIns().enableAbsolute();
	CImageManager::getIns().find("system_dress_guage")->DrawRectwithBlend(240, 480 - 32, 160, 32,
		0xFFFFFF, CImageManager::BLENDMODE::BM_NONE, 0, 7, (input.lock()->Select() > 0) ? 1 : 0);
	if (pauseGuage == Constant::MaxPause)CImageManager::getIns().find("system_dress_guage")->DrawRectwithBlend(240, 480 - 32, 160, 32,
		0xFFFFFF, CImageManager::BLENDMODE::BM_NONE, 0, 8, 2);
	CImageManager::getIns().find("system_dress_guage")->DrawRectwithBlend(240, 480 - 32, 160 * ((float)pauseGuage / 180), 32,
		HSV2RGB((float)(cnt % 60) / 60, 1.0, 1.0), CImageManager::BLENDMODE::BM_SUB, 0x7F, 9, (input.lock()->Select() > 0) ? 1 : 0);
	CAnchor::getIns().disableAbsolute();

	if (isPause)
		RenderDresschangeMenu();

#ifdef _DEBUG
	printfDx("Money:%d\nGraphHandle:%d\n", reserveMoney, GetGraphNum());
#endif
}

void CGameMediator::UpdateDresschangeMenu() {
	if (input.lock()->Select() == 1) {
		isPause = false;
		pauseGuage = 0;
		return;
	}
	CCostumeFactory CCF;
	costumeNowFocusOn = std::make_unique<CCostumeBase*>(CCF.create("C_Festa"));
}

void CGameMediator::RenderDresschangeMenu()const {
	CAnchor::getIns().enableAbsolute();
	CImageManager::getIns().find("system_curtain")->Draw(0, 0, 100, 0);
	CImageManager::getIns().find("system_curtain")->Draw(320, 0, 100, 1);
	for (int i = 0; i < 6; i++) {
		CImageManager::getIns().find("system_status_guage")->Draw(360, 80 + i * 64, 103, 1);
		CImageManager::getIns().find("system_status_guage")->Draw(360, 80 + i * 64, 101, 3);
		CImageManager::getIns().find("system_status_guage")->Draw(360, 96 + i * 64, 103, 1);
		CImageManager::getIns().find("system_status_guage")->Draw(360, 96 + i * 64, 101, 3);
		CImageManager::getIns().find("system_status_guage")->Draw(360, 64 + i * 64, 103, 0);
		CImageManager::getIns().find("system_status_name")->Draw(360 + 80, 64 + i * 64, 103, i);
		switch (i) {
		case 0:
			CImageManager::getIns().find("system_status_guage")->DrawRectwithBlend(360, 80 + i * 64,
				240 * min(1.0, max(0.02, (player->costume->constants.FrictionCF - minFric) / max(0.0001, maxFric - minFric))), 16, 0xFFFFFF, CImageManager::BLENDMODE::BM_NONE, 0, 102, 2);
			CImageManager::getIns().find("system_status_guage")->DrawRectwithBlend(360, 96 + i * 64,
				240 * min(1.0, max(0.02, ((*costumeNowFocusOn)->constants.FrictionCF - minFric) / max(0.0001, maxFric - minFric))), 16, 0xFFFFFF, CImageManager::BLENDMODE::BM_NONE, 0, 102, 2);
			break;
		case 1:
			CImageManager::getIns().find("system_status_guage")->DrawRectwithBlend(360, 80 + i * 64,
				240 * min(1.0, max(0.02, (player->costume->constants.WaterResCF - minWaterRes) / max(0.0001, maxWaterRes - minWaterRes))), 16, 0xFFFFFF, CImageManager::BLENDMODE::BM_NONE, 0, 102, 2);
			CImageManager::getIns().find("system_status_guage")->DrawRectwithBlend(360, 96 + i * 64,
				240 * min(1.0, max(0.02, ((*costumeNowFocusOn)->constants.WaterResCF - minWaterRes) / max(0.0001, maxWaterRes - minWaterRes))), 16, 0xFFFFFF, CImageManager::BLENDMODE::BM_NONE, 0, 102, 2);
			break;
		case 2:
			CImageManager::getIns().find("system_status_guage")->DrawRectwithBlend(360, 80 + i * 64,
				240 * min(1.0, max(0.02, (player->costume->constants.AirResCF - minAirRes) / max(0.0001, maxAirRes - minAirRes))), 16, 0xFFFFFF, CImageManager::BLENDMODE::BM_NONE, 0, 102, 2);
			CImageManager::getIns().find("system_status_guage")->DrawRectwithBlend(360, 96 + i * 64,
				240 * min(1.0, max(0.02, ((*costumeNowFocusOn)->constants.AirResCF - minAirRes) / max(0.0001, maxAirRes - minAirRes))), 16, 0xFFFFFF, CImageManager::BLENDMODE::BM_NONE, 0, 102, 2);
			break;
		case 3:
			CImageManager::getIns().find("system_status_guage")->DrawRectwithBlend(360, 80 + i * 64,
				240 * min(1.0, max(0.02, (player->costume->Mass - minMass) / max(0.0001, maxMass - minMass))), 16, 0xFFFFFF, CImageManager::BLENDMODE::BM_NONE, 0, 102, 2);
			CImageManager::getIns().find("system_status_guage")->DrawRectwithBlend(360, 96 + i * 64,
				240 * min(1.0, max(0.02, ((*costumeNowFocusOn)->Mass - minMass) / max(0.0001, maxMass - minMass))), 16, 0xFFFFFF, CImageManager::BLENDMODE::BM_NONE, 0, 102, 2);
			break;
		case 4:
			CImageManager::getIns().find("system_status_guage")->DrawRectwithBlend(360, 80 + i * 64,
				240 * min(1.0, max(0.02, (player->costume->MaxSpeed - minVelocity) / max(0.0001, maxVelocity - minVelocity))), 16, 0xFFFFFF, CImageManager::BLENDMODE::BM_NONE, 0, 102, 2);
			CImageManager::getIns().find("system_status_guage")->DrawRectwithBlend(360, 96 + i * 64,
				240 * min(1.0, max(0.02, ((*costumeNowFocusOn)->MaxSpeed - minVelocity) / max(0.0001, maxVelocity - minVelocity))), 16, 0xFFFFFF, CImageManager::BLENDMODE::BM_NONE, 0, 102, 2);
			break;
		case 5:
			CImageManager::getIns().find("system_status_guage")->DrawRectwithBlend(360, 80 + i * 64,
				240 * min(1.0, max(0.02, (player->costume->Accelaration - minAccel) / max(0.0001, maxAccel - minAccel))), 16, 0xFFFFFF, CImageManager::BLENDMODE::BM_NONE, 0, 102, 2);
			CImageManager::getIns().find("system_status_guage")->DrawRectwithBlend(360, 96 + i * 64,
				240 * min(1.0, max(0.02, ((*costumeNowFocusOn)->Accelaration - minAccel) / max(0.0001, maxAccel - minAccel))), 16, 0xFFFFFF, CImageManager::BLENDMODE::BM_NONE, 0, 102, 2);
			break;
		}
	}
	CAnchor::getIns().disableAbsolute();
}