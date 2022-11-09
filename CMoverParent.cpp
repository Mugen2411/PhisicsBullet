#include "CMoverParent.h"
#include "CMover_Player.h"
#include <algorithm>
#include <iterator>

CMoverParent::CMoverParent(std::weak_ptr<CGameMediator> m) :med(m), moverList(), reserveList(), cnt(0)
{
}

std::weak_ptr<CMover> CMoverParent::getMover(int ID, int num)
{
	int i = 0;
	for(std::shared_ptr<CMover> v : moverList)
	{
		if (v->Category == ID) {
			if (i == num)return v;
			i++;
		}
	}
	return std::weak_ptr<CMover>();
}

void CMoverParent::Update()
{	
	Hit();
	int r = 0;
	for (auto itr = moverList.begin(); itr != moverList.end();) {
		(*itr)->BaseUpdate();
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
		if(itr->BaseRender())itr->Render();
		});
#ifdef _DEBUG
	printfDx("Objects: %d\n", moverList.size());
#endif
}

void CMoverParent::Hit()
{
	for (std::shared_ptr<CMover> i : moverList) {
		for (std::shared_ptr<CMover> j : moverList) {
			if (i == j)continue;
			if ((i->Position - j->Position).getLength2() < (i->getSize() + j->getSize())* (i->getSize() + j->getSize())) {
				i->HitDispatch(j);
			}
		}
	}
}
