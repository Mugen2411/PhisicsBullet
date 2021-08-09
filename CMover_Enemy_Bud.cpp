#include "CMover_Enemy_Bud.h"
#include "CImageManager.h"
#include "CMover_Bullet_Corn.h"

CMover_Enemy_Bud::CMover_Enemy_Bud(CVector position, int Level):
	CMover_EnemyBase(Level, CAttribute(1.0, 0.5, 1.0, 1.0, 1.0, 1.0),position, 18.0, 2.0),testDest(0.0, 0.0)
{
}

int CMover_Enemy_Bud::Update()
{
	switch (state) {
	case 0:
	case 1:
		cnt++;
		if (cnt == 90) {
			CVector ppos = med.lock()->GetPlayerPosition();
			if(!!ppos)med.lock()->RegisterMover(std::make_shared<CMover_Bullet_Corn>(baseParams, Position, (ppos-Position).getAngle()));
			cnt = 0;
			testDest.x = GetRand(640);
			testDest.y = GetRand(480);
		}
		Walk(testDest);
		animCount += 0.3;
		if (animCount > 4)animCount = 0;
		break;
	case -1:
		animCount += 0.1;
		if (animCount > 4) {
			state = 0;
			animCount = 0;
			cnt = 0;
			testDest.x = GetRand(640);
			testDest.y = GetRand(480);
		}
		break;
	}
#ifdef _DEBUG
	printfDx("V:%lf,%lf\nA:%lf,%lf\n", Velocity.x, Velocity.y, Acceleration.x, Acceleration.y);
#endif
	return 0;
}

void CMover_Enemy_Bud::Render() const
{
#ifdef _DEBUG
	printfDx("state:%d\n", state);
	DrawCircle(testDest.x, testDest.y, 8, 0xFFFF00);
#endif
	if (state < 0) {
		CImageManager::getIns().find("enemy_bud_intro")->DrawRota(Position.x, Position.y, 0.0, 1.0, 0.0, (int)(animCount));
		return;
	}
	CImageManager::getIns().find("enemy_bud")->DrawRota(Position.x, Position.y, 0.0, 1.0, 0.0, Direction * 4 + (int)(animCount));
}

void CMover_Enemy_Bud::Dead()
{
}

void CMover_Enemy_Bud::Disappear()
{
}
