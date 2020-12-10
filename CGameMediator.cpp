#include "CGameMediator.h"
#include "CMoverParent.h"
#include "CFieldParent.h"
#include "CPowerParent.h"
#include "CControllerFactory.h"
#include "CMover.h"

CGameMediator::CGameMediator()
{
	CreateParts();
	CControllerFactory::getIns();

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
	powerParent->Update();
	moverParent->Update();
	fieldParent->Update();
}

void CGameMediator::Render() const
{
	fieldParent->Render();
	moverParent->Render();
	powerParent->Render();
}
