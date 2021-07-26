#include "CGameMediator.h"
#include "CMoverParent.h"
#include "CFieldParent.h"
#include "CPowerParent.h"
#include "CEffectParent.h"
#include "CMover_Player.h"
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
	RegisterMover(std::make_shared<CMover_Player>(CVector(8, 8), 24.0, 4.0));
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
