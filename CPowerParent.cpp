#include "CPowerParent.h"
#include "CPower.h"
#include "CPower_Line.h"

CPowerParent::CPowerParent(CGameMediator* m) : med(m)
{
}

void CPowerParent::Add(const std::shared_ptr<CPower>& p)
{
	p->setParent(this);
	powerList.push_back(p);
}

void CPowerParent::ApplyForceToMover(CMover* m)
{
	for (auto itr = powerList.begin(); itr != powerList.end(); itr++) {
		(*itr)->ApplyForceToMover(m);
	}
}

void CPowerParent::Update()
{
	int r = 0;
	for (auto itr = powerList.begin(); itr != powerList.end();) {
		r = (*itr)->Update();
		switch (r) {
		case 0:
			break;
		case 1:
			itr = powerList.erase(itr);
			continue;
			break;
		}
		itr++;
	}
}

void CPowerParent::Render()
{
	for (auto itr = powerList.begin(); itr != powerList.end(); itr++) {
		(*itr)->Render();
	}
}
