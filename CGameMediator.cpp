#include "CGameMediator.h"
#include "CMoverParent.h"
#include "CFieldParent.h"
#include "CPowerParent.h"
#include "CMover.h"

CGameMediator::CGameMediator(SceneManager* ScnMng):Scene_Abstract(ScnMng), isPause(false)
{
	CreateParts();
	input = CControllerFactory::getIns().getController();
}

void CGameMediator::CreateParts()
{
	moverParent = std::make_shared<CMoverParent>(this);
	fieldParent = std::make_shared<CFieldParent>(this);
	powerParent = std::make_shared<CPowerParent>(this);
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
		//if (pauseGuage == 120)isPause = true;
	}
	input->update();
}

void CGameMediator::Render() const
{
	fieldParent->Render();
	moverParent->Render();
	powerParent->Render();
}
