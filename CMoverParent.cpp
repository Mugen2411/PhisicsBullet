#include "CMoverParent.h"
#include "CMover_Player.h"
#include "CMover_TestBullet.h"
#include <algorithm>

CMoverParent::CMoverParent(CGameMediator* m) :med((CGameMediator*)m), moverList(), cnt(0)
{
	moverList.push_back(std::make_shared<CMover_Player>(CVector(320, 320), 24.0, 4.0));
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

	if (cnt % 60 == 0) {
		CVector p = CVector(rand()%(640-64*2)+64, rand()%(480-64*2)+64);
		for (int i = 0; i < 32; i++) {
			CVector v = CVector(cos(3.14 / 16 * i) * 3.0, sin(3.14 / 16 * i) * 3.0);
			moverList.push_back(std::make_shared<CMover_TestBullet>(p, v));
		}
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
