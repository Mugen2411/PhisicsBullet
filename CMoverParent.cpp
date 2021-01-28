#include "CMoverParent.h"
#include "CMover_Player.h"
#include "CMover_TestBullet.h"
#include <algorithm>

CMoverParent::CMoverParent(CGameMediator* m) :med((CGameMediator*)m), moverList(), cnt(0)
{
	moverList.push_back(std::make_shared<CMover_Player>(CVector(320, 320), 15.0, 3.0));
}

void CMoverParent::Update()
{	
	int r = 0;
	for (auto itr = moverList.begin(); itr != moverList.end();) {
		r = (*itr)->Update();
		med->ApplyForceToMover(itr->get());
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
