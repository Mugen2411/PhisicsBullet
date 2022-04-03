#include "CMover_Enemy_Bud.h"
#include "CImageManager.h"
#include "CMover_Bullet_Corn.h"
#include "CNumberDrawer.h"

CMover_Enemy_Bud::CMover_Enemy_Bud(CVector position, int Level):
	CMover_EnemyBase(20, Level,0.5, 1.0, 0.8, CAttribute(1.0).FIRE(0.4).FLOWER(2.0), 10, 0xFFFF00, position, 3.0, 2.0, 0.8, 0.7, 0.9),
	testDest(0.0, 0.0)
{
}

int CMover_Enemy_Bud::Update()
{
	switch (state) {
	case 0:
	case 1:
		cnt++;
		if (cnt == 90) {
			Find_Route();
			CVector ppos = med.lock()->GetPlayerPosition();
			if(!!ppos)med.lock()->RegisterMover(std::make_shared<CMover_Bullet_Corn>(baseParams, Position, (ppos-Position).getAngle()));
			cnt = 0;
		}
		Move_on_Route();
		animCount += 0.3;
		if (animCount > 4)animCount = 0;
		break;
	case -1:
		animCount += 0.1;
		if (animCount > 4) {
			state = 0;
			Find_Route();
			animCount = 0;
			cnt = 0;
		}
		break;
	}
#ifdef _DEBUG
	printfDx("V:%lf,%lf\nA:%lf,%lf\n", Velocity.x, Velocity.y, Acceleration.x, Acceleration.y);
#endif
	return Status;
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

	Render_HPGuage();
}

CMover_EnemyBase* CMover_Enemy_Bud::Clone(CVector Position, int Level)
{
	return new CMover_Enemy_Bud(Position, Level);
}
