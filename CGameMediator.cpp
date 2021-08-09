#include "CGameMediator.h"
#include "CMoverParent.h"
#include "CFieldParent.h"
#include "CPowerParent.h"
#include "CEffectParent.h"
#include "CMover_Player.h"
#include "CMover_Enemy_Bud.h"
#include "CMover.h"

CGameMediator::CGameMediator(SceneManager* ScnMng):Scene_Abstract(ScnMng), isPause(false)
{
	input = CControllerFactory::getIns().getController();
}

CGameMediator::~CGameMediator()
{
	OutputDebugString("CGameMediatorは消えてる");
}

void CGameMediator::CreateParts()
{
	moverParent = std::make_shared<CMoverParent>(shared_from_this());
	fieldParent = std::make_shared<CFieldParent>(shared_from_this(), "media/map/0.map");
	powerParent = std::make_shared<CPowerParent>(shared_from_this());
	RegisterMover(std::make_shared<CMover_Player>(CVector(8*32, 8*32), 24.0, 4.0));
	for (int i = 0; i < 10; i++) {
		RegisterMover(std::make_shared<CMover_Enemy_Bud>(CVector((GetRand(16)+2) * 32+16, (GetRand(11) + 2)*32+16), 5));
	}
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

void CGameMediator::Update()
{
	if (isPause) {
		if (input->A() == 1) {
			isPause = false;
			pauseGuage = 0;
		}
	} else {
		pauseGuage++;
		powerParent->Update();
		moverParent->Update();
		fieldParent->Update();
		CEffectParent::Update();
		//if (pauseGuage == 120)isPause = true;
	}
	input->update();
}

void CGameMediator::Render() const
{
	fieldParent->Render();
	moverParent->Render();
	powerParent->Render();
	CEffectParent::Render();
}
