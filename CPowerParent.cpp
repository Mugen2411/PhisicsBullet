#include "CPowerParent.h"
#include "CPower.h"
#include "CPower_Line.h"

CPowerParent::CPowerParent(CGameMediator* m) : med(m)
{
	//for (int i = 0; i < 6; i++) {
	//	powerList.push_back(std::make_shared<CPower_Line>(this, CVector(320, 240), CVector(Constant::PI / 12 + Constant::PI * i / 3, 160), 64, 3.0));
	//}
}

void CPowerParent::Add(std::shared_ptr<CPower> p)
{
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
