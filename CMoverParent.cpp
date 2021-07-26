#include "CMoverParent.h"
#include "CMover_Player.h"
#include <algorithm>
#include <iterator>

CMoverParent::CMoverParent(std::shared_ptr<CGameMediator> m) :med(m), moverList(), reserveList(), cnt(0)
{
}

void CMoverParent::RegisterMover(std::shared_ptr<CMover> m)
{
	reserveList.push_back(m);
}

void CMoverParent::Update()
{	
	int r = 0;
	for (auto itr = moverList.begin(); itr != moverList.end();) {
		r = (*itr)->Update();
		med.lock()->ApplyForceToMover(itr->get());
		(*itr)->Move();
		switch (r) {
		case 0:
			break;
		case 1:
			(*itr)->Dead();
			itr = moverList.erase(itr);
			continue;
			break;
		case 2:
			(*itr)->Disappear();
			itr = moverList.erase(itr);
			continue;
			break;
		}
		itr++;
	}
	if (reserveList.size() > 0) {
		std::copy(reserveList.begin(), reserveList.end(), std::back_inserter(moverList));
		reserveList.clear();
	}
	cnt++;
}

void CMoverParent::Render()
{
	std::for_each(moverList.begin(), moverList.end(), [](std::shared_ptr<CMover> itr) {
		itr->Render();
		});
#ifdef _DEBUG
	printfDx("Objects: %d\n", moverList.size());
#endif
}
