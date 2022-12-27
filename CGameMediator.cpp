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
#include "CEnemySpawner.h"
#include "CProgressData.h"
#include "CEffect_Bright.h"

void CGameMediator::ProcessEnemySpawner()
{
	for (auto i = enemySpawner.begin(); i != enemySpawner.end();) {
		int r = (*i)->Update();
		if (r == 1) {
			i = enemySpawner.erase(i);
			continue;
		}
		++i;
	}
}

CGameMediator::CGameMediator(SceneManager* ScnMng) :Scene_Abstract(ScnMng), isPause(true), isRetire(false), pauseGuage(0), cnt(0), isInitialized(false),
costumeSelecterCNT(12), isCostumeSelecterEnd(false), nowLevelOfStage(CProgressData::getIns().getCurrentStage() * 3), CND()
{
	input = CControllerFactory::getIns().getController();
	retireText[0] = CTextDrawer::Text("本当にリタイアしますか？", CVector(320 - 6 * 36, 32), 0xFFFFFF, 0x000000, 1);
	retireText[1] = CTextDrawer::Text("SPACEキーを押すとタイトル画面に戻ります。", CVector(320 - 10 * 12, 320), 0xFFFFFF, 0x00CFCF, 0);
	waveNumber = CTextDrawer::Text(std::string("WAVE:") + std::to_string(CProgressData::getIns().getCurrentStage() + 1), 
		CVector(320 + 88, 8), 0xFFFFFF, 0x000000, 1);
	skillList = CPassiveSkill::getIns().getGotSkillList();
	skillLevelList = CPassiveSkill::getIns().getGotSkillLevelList();
}

CGameMediator::~CGameMediator()
{
}

void CGameMediator::CreateParts()
{
	moverParent = std::make_unique<CMoverParent>(this);
	fieldParent = std::make_unique<CFieldParent>(this, CProgressData::getIns().getMapFilepath());
	powerParent = std::make_unique<CPowerParent>(this);

	CVector playerPos;
	fieldParent->convertSpawner(enemySpawner, nowLevelOfStage, playerPos);
	fieldParent->readDefine();
	CCostumeFactory CCF;
	CCF.getMinMaxFriction(minFric, maxFric);
	CCF.getMinMaxWaterRes(minWaterRes, maxWaterRes);
	CCF.getMinMaxAirRes(minAirRes, maxAirRes);
	CCF.getMinMaxMass(minMass, maxMass);
	CCF.getMinMaxVelocity(minVelocity, maxVelocity);
	CCF.getMinMaxAccel(minAccel, maxAccel);
	costumeNowFocusOn = std::make_unique<CCostumeBase*>(CCF.create("C_Uniform"));
	RegisterMover(player = std::make_shared<CMover_Player>(playerPos, CProgressData::getIns().getPlayerLevel(), CCF.create("C_Uniform")));
	CSoundManager::getIns().find("bgm")->Play(CSound::PT_LOOP);
	CEffectParent::Reset();
	CEffect_Bright::getIns().inactivate();
	isInitialized = true;
}

void CGameMediator::RegisterMover(std::shared_ptr<CMover> m)
{
	m->setMediator(this);
	moverParent->RegisterMover(m);
}

void CGameMediator::ApplyForceToMover(CMover* m)
{
	powerParent->ApplyForceToMover(m);
	fieldParent->ApplyForceToMover(m);
}

bool CGameMediator::HitToMover(CMover* m)
{
	return fieldParent->HitToMover(m);
}

CVector CGameMediator::GetPlayerPosition()
{
	std::weak_ptr<CMover> p = moverParent->getMover(CMover::MOVER_ID::MV_PLAYER, 0);
	if (!p.lock())return CVector(false);
	return CVector(p.lock()->getPosition());
}

std::list<CVector> CGameMediator::GetRoute(CVector start, CVector goal, CAttribute attrDEF, int distance)
{
	return fieldParent->getRoute(start, goal, attrDEF, distance);
}

std::vector<CVector> CGameMediator::GetTargetByDistance(CVector start, int distance)
{
	return fieldParent->getTargetByDistance(start, distance);
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
	if (!isInitialized)
		return;
	cnt++;
	if (isRetire) {
		UpdateRetireMenu();
		return;
	}
	if (isPause) {
		UpdateDresschangeMenu();
		return;
	}
#ifdef _DEBUG
	if (input.lock()->Start() == 1) {
		CEffect_Bright::getIns().inactivate();
		scn_mng->ChangeScene(Constant::SCENE_ID::SCENE_EDITOR, true);
		return;
	}
#endif
	if (player->getHP() < 0) {
		CSoundManager::getIns().find("bgm")->Stop();
		CSoundManager::getIns().find("player_dead")->Play(CSound::PLAYTYPE::PT_BACK);
		CProgressData::getIns().lose(reserveMoney);
		CEffect_Bright::getIns().inactivate();
		scn_mng->ChangeScene(Constant::SCENE_ID::SCENE_GAMEOVER, false);
		return;
	}
	if (moverParent->getCountByCategory(CMover::MOVER_ID::MV_ENEMY) == 0 && enemySpawner.empty()) {
		CSoundManager::getIns().find("bgm")->Stop();
		CSoundManager::getIns().find("success")->Play(CSound::PLAYTYPE::PT_BACK);
		CProgressData::getIns().win(reserveMoney);
		CEffect_Bright::getIns().inactivate();
		if (CProgressData::getIns().getCurrentStage() == CProgressData::getIns().getMaxStage() - 1) {
			if (CProgressData::getIns().getEndless()) {
				scn_mng->ChangeScene(Constant::SCENE_ID::SCENE_STAGECLEAR, false);
			}else scn_mng->ChangeScene(Constant::SCENE_ID::SCENE_GAMECLEAR, false);
		}
		else {
			scn_mng->ChangeScene(Constant::SCENE_ID::SCENE_STAGECLEAR, false);
		}
		return;
	}
	CEnemyFactory CEF;
	++pauseGuage;
	pauseGuage = min(pauseGuage, Constant::MaxPause);
	if (input.lock()->Select() == 1) {
		if (pauseGuage == Constant::MaxPause) {
			isPause = true;
			costumeSelecterCNT = 0;
			CEffect_Bright::getIns().inactivate();
		}
	}
	ProcessEnemySpawner();
	if (moverParent->getCountByCategory(CMover::MOVER_ID::MV_ENEMY) == 0) {
		ProcessEnemySpawner();
	}
	CEffect_Bright::getIns().Clear();
	powerParent->Update();
	moverParent->Update();
	fieldParent->Update();
	CEffectParent::Update();
}

void CGameMediator::Render() const
{
	fieldParent->Render();
	moverParent->Render();
	powerParent->Render();
	CEffectParent::Render();
	CAnchor::getIns().enableAbsolute();
	CTextDrawer::getIns().Register(waveNumber);
	CImageManager::getIns().find("system_dress_guage")->DrawRectwithBlend(240, 480 - 32, 160, 32,
		0xFFFFFF, CImageManager::BLENDMODE::BM_NONE, 0, 7, (input.lock()->Select() > 0) ? 1 : 0);
	if (pauseGuage == Constant::MaxPause)CImageManager::getIns().find("system_dress_guage")->DrawRectwithBlend(240, 480 - 32, 160, 32,
		0xFFFFFF, CImageManager::BLENDMODE::BM_NONE, 0, 8, 2);
	CImageManager::getIns().find("system_dress_guage")->DrawRectwithBlend(240, 480 - 32, 160 * ((float)pauseGuage / Constant::MaxPause), 32,
		HSV2RGB((float)(cnt % 60) / 60, 1.0, 1.0), CImageManager::BLENDMODE::BM_SUB, 0x7F, 9, (input.lock()->Select() > 0) ? 1 : 0);
	CND.Draw(540, 16, reserveMoney, 0, 2, Constant::priority_number);
	CImageManager::getIns().find("system_passive_frame")->Draw(24, 480 - 48, 102 + 1);
	for (int i = 0; i < 5; i++) {
		if (i < skillList.size()) {
			CImageManager::getIns().find("icon_passiveskill")->Draw(1 + 24 + 32 * i, 480-48 + 1, 102, skillList[i]);
			CImageManager::getIns().find("icon_passive_progress")->Draw(1 + 24 + 32 * i, 480 - 48 + 1, 102, skillLevelList[i]);
		}
		else CImageManager::getIns().find("icon_passive_covered")->Draw(1 + 24 + 32 * i, 480 - 48 + 1, 102);
	}
	CAnchor::getIns().disableAbsolute();

	if (isRetire) {
		RenderRetireMenu();
		return;
	}
	if (isPause) {
		RenderDresschangeMenu();
		return;
	}

#ifdef _DEBUG
	printfDx("Money:%d\nGraphHandle:%d\n", reserveMoney, GetGraphNum());
#endif
}

void CGameMediator::UpdateDresschangeMenu() {
	static CCostumeFactory CCF;
	static int currentCostumeIndex = 0;
	costumeNowFocusOn = std::make_unique<CCostumeBase*>(CCF.create(currentCostumeIndex));
	costumeSelecterCNT = min(isCostumeSelecterEnd ? --costumeSelecterCNT : ++costumeSelecterCNT, 12);
	if (isCostumeSelecterEnd) {
		if (costumeSelecterCNT != 0)return;
		costumeSelecterCNT = 0;
		isPause = false;
		isCostumeSelecterEnd = false;
		return;
	}
	if (input.lock()->Select() == 1) {
		isCostumeSelecterEnd = true;
		pauseGuage = 0;
		player->ChangeCostume(CCF.create(currentCostumeIndex));
		CEffect_Bright::getIns().activate();
		return;
	}
	if (input.lock()->Start() == 1) {
		isRetire = true;
		return;
	}
	if (input.lock()->Right() == 1) {
		currentCostumeIndex += 1;
		currentCostumeIndex %= CCF.getSize();
	}
	if (input.lock()->Left() == 1) {
		currentCostumeIndex += CCF.getSize() - 1;
		currentCostumeIndex %= CCF.getSize();
	}
}

void CGameMediator::RenderDresschangeMenu()const {
	CAnchor::getIns().enableAbsolute();
	CImageManager::getIns().find("system_curtain")->Draw(0 - (12 - costumeSelecterCNT) / 12.0 * 320, 0, 100, 0);
	CImageManager::getIns().find("system_curtain")->Draw(320 + (12 - costumeSelecterCNT) / 12.0 * 320, 0, 100, 1);
	CImageManager::getIns().find("system_costume_frame")->DrawRota(160, 64, 0.0f, 1.0f, 102);
	CImageManager::getIns().find((*costumeNowFocusOn)->GID)->DrawRota(160, 64, 0.0f, 1.0f, 101, 4);
	for (int i = 0; i < 6; i++) {
		CImageManager::getIns().find("system_status_guage")->Draw(360, 80 + i * 64, 103, 1);
		CImageManager::getIns().find("system_status_guage")->Draw(360, 80 + i * 64, 101, 3);
		CImageManager::getIns().find("system_status_next_now")->Draw(344, 80 + i * 64, 101, 1);
		CImageManager::getIns().find("system_status_guage")->Draw(360, 96 + i * 64, 103, 1);
		CImageManager::getIns().find("system_status_guage")->Draw(360, 96 + i * 64, 101, 3);
		CImageManager::getIns().find("system_status_next_now")->Draw(344, 96 + i * 64, 101, 0);
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
				240 * min(1.0, max(0.02, ((1.0 - player->costume->constants.WaterResCF) - minWaterRes) / max(0.0001, maxWaterRes - minWaterRes))), 16, 0xFFFFFF, CImageManager::BLENDMODE::BM_NONE, 0, 102, 2);
			CImageManager::getIns().find("system_status_guage")->DrawRectwithBlend(360, 96 + i * 64,
				240 * min(1.0, max(0.02, ((1.0 - (*costumeNowFocusOn)->constants.WaterResCF) - minWaterRes) / max(0.0001, maxWaterRes - minWaterRes))), 16, 0xFFFFFF, CImageManager::BLENDMODE::BM_NONE, 0, 102, 2);
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
	const int icon_left = 64;
	for (int i = 0; i < 6; i++) {
		switch (i) {
		case 0:
			CImageManager::getIns().find("icon_attribute")->Draw(icon_left + 32 * i + 0, 96, 101, i);
			if ((*costumeNowFocusOn)->AttributeDEF.None > 1.0) {
				CImageManager::getIns().find("icon_weak_or_strong")->Draw(icon_left + 32 * i + 16, 96, 101, 0);
			}
			else if ((*costumeNowFocusOn)->AttributeDEF.None < 1.0) {
				CImageManager::getIns().find("icon_weak_or_strong")->Draw(icon_left + 32 * i + 16, 96, 101, 1);
			}
			else {
				CImageManager::getIns().find("icon_weak_or_strong")->Draw(icon_left + 32 * i + 16, 96, 101, 2);
			}
			break;
		case 1:
			CImageManager::getIns().find("icon_attribute")->Draw(icon_left + 32 * i + 0, 96, 101, i);
			if ((*costumeNowFocusOn)->AttributeDEF.Fire > 1.0) {
				CImageManager::getIns().find("icon_weak_or_strong")->Draw(icon_left + 32 * i + 16, 96, 101, 0);
			}
			else if ((*costumeNowFocusOn)->AttributeDEF.Fire < 1.0) {
				CImageManager::getIns().find("icon_weak_or_strong")->Draw(icon_left + 32 * i + 16, 96, 101, 1);
			}
			else {
				CImageManager::getIns().find("icon_weak_or_strong")->Draw(icon_left + 32 * i + 16, 96, 101, 2);
			}
			break;
		case 2:
			CImageManager::getIns().find("icon_attribute")->Draw(icon_left + 32 * i + 0, 96, 101, i);
			if ((*costumeNowFocusOn)->AttributeDEF.Aqua > 1.0) {
				CImageManager::getIns().find("icon_weak_or_strong")->Draw(icon_left + 32 * i + 16, 96, 101, 0);
			}
			else if ((*costumeNowFocusOn)->AttributeDEF.Aqua < 1.0) {
				CImageManager::getIns().find("icon_weak_or_strong")->Draw(icon_left + 32 * i + 16, 96, 101, 1);
			}
			else {
				CImageManager::getIns().find("icon_weak_or_strong")->Draw(icon_left + 32 * i + 16, 96, 101, 2);
			}
			break;
		case 3:
			CImageManager::getIns().find("icon_attribute")->Draw(icon_left + 32 * i + 0, 96, 101, i);
			if ((*costumeNowFocusOn)->AttributeDEF.Thunder > 1.0) {
				CImageManager::getIns().find("icon_weak_or_strong")->Draw(icon_left + 32 * i + 16, 96, 101, 0);
			}
			else if ((*costumeNowFocusOn)->AttributeDEF.Thunder < 1.0) {
				CImageManager::getIns().find("icon_weak_or_strong")->Draw(icon_left + 32 * i + 16, 96, 101, 1);
			}
			else {
				CImageManager::getIns().find("icon_weak_or_strong")->Draw(icon_left + 32 * i + 16, 96, 101, 2);
			}
			break;
		case 4:
			CImageManager::getIns().find("icon_attribute")->Draw(icon_left + 32 * i + 0, 96, 101, i);
			if ((*costumeNowFocusOn)->AttributeDEF.Flower > 1.0) {
				CImageManager::getIns().find("icon_weak_or_strong")->Draw(icon_left + 32 * i + 16, 96, 101, 0);
			}
			else if ((*costumeNowFocusOn)->AttributeDEF.Flower < 1.0) {
				CImageManager::getIns().find("icon_weak_or_strong")->Draw(icon_left + 32 * i + 16, 96, 101, 1);
			}
			else {
				CImageManager::getIns().find("icon_weak_or_strong")->Draw(icon_left + 32 * i + 16, 96, 101, 2);
			}
			break;
		case 5:
			CImageManager::getIns().find("icon_attribute")->Draw(icon_left + 32 * i + 0, 96, 101, i);
			if ((*costumeNowFocusOn)->AttributeDEF.Ice > 1.0) {
				CImageManager::getIns().find("icon_weak_or_strong")->Draw(icon_left + 32 * i + 16, 96, 101, 0);
			}
			else if ((*costumeNowFocusOn)->AttributeDEF.Ice < 1.0) {
				CImageManager::getIns().find("icon_weak_or_strong")->Draw(icon_left + 32 * i + 16, 96, 101, 1);
			}
			else {
				CImageManager::getIns().find("icon_weak_or_strong")->Draw(icon_left + 32 * i + 16, 96, 101, 2);
			}
			break;
		}
	}
	CImageManager::getIns().find("system_dress_guage")->DrawRectwithBlend(240, 480 - 32, 160, 32,
		0xFFFFFF, CImageManager::BLENDMODE::BM_NONE, 0, 101, (input.lock()->Select() > 0) ? 1 : 0);
	CImageManager::getIns().find("system_dress_guage")->DrawRectwithBlend(240, 480 - 32, 160, 32,
		0xFFFFFF, CImageManager::BLENDMODE::BM_NONE, 0, 102, 2);
	CImageManager::getIns().find("system_dress_guage")->DrawRectwithBlend(240, 480 - 32, 160, 32,
		HSV2RGB((float)(cnt % 60) / 60, 1.0, 1.0), CImageManager::BLENDMODE::BM_SUB, 0x7F, 103, (input.lock()->Select() > 0) ? 1 : 0);
	CImageManager::getIns().find("icon_return")->Draw(0, 0, 101);
	CAnchor::getIns().disableAbsolute();
	CTextDrawer::getIns().RegisterForCostumeDetail((*costumeNowFocusOn)->detail);
}

void CGameMediator::UpdateRetireMenu()
{
	if (input.lock()->Start() == 1) {
		isRetire = false;
		return;
	}
	if (input.lock()->Select() == 1) {
		CSoundManager::getIns().find("bgm")->Stop();
		scn_mng->ChangeScene(Constant::SCENE_ID::SCENE_TITLE, true);
		return;
	}
}

void CGameMediator::RenderRetireMenu()const
{
	CAnchor::getIns().enableAbsolute();
	CImageManager::getIns().find("system_curtain")->Draw(0, 0, 100, 0);
	CImageManager::getIns().find("system_curtain")->Draw(320, 0, 100, 1);
	CImageManager::getIns().find("icon_return")->Draw(0, 0, 101);
	for (auto& i : retireText) {
		CTextDrawer::getIns().Register(i);
	}
	CAnchor::getIns().disableAbsolute();
}
