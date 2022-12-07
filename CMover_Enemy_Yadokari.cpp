#include "CMover_Enemy_Yadokari.h"
#include "CImageManager.h"
#include "CMover_Bullet_WaterSplash.h"
#include "CNumberDrawer.h"

CMover_Enemy_Yadokari::CMover_Enemy_Yadokari(CVector position, int Level) :
	CMover_EnemyBase(40, Level, 1.0, 1.0, CAttribute(1.5).AQUA(4.0).THUNDER(0.3).FLOWER(0.4), 18, 0xFF7F00, position, 3.0, 1.8, COF(0.2, 0.1, 0.6, 0.0)),
	testDest(0.0, 0.0)
{
}

int CMover_Enemy_Yadokari::Update()
{
	switch (state) {
	case 0:
	case 1:
		cnt++;
		if (cnt == 90) {
			Find_Route();
			CVector ppos = med.lock()->GetPlayerPosition();
			if (!!ppos && route.size() <= 5) {
				for (int i = 0; i < 3; i++) {
					med.lock()->RegisterMover(std::make_shared<CMover_Bullet_WaterSplash>(baseParams, Position, (ppos - Position).getAngle(), 7.0+i*3.0));
				}
			}
			cnt = 0;
		}
		if (route.size() >= 5)Move_on_Route();
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
	return Status;
}

void CMover_Enemy_Yadokari::Render() const
{
	if (state < 0) {
		CImageManager::getIns().find("enemy_bud_intro")->DrawRota(Position.x, Position.y, 0.0, 1.0, Constant::priority_enemy, (int)(animCount));
		return;
	}
	CImageManager::getIns().find("enemy_yadokari")->DrawRota(Position.x, Position.y, 0.0, 1.0, Constant::priority_enemy, Direction * 4 + (int)(animCount));
}

CMover_EnemyBase* CMover_Enemy_Yadokari::Clone(CVector Position, int Level)
{
	return new CMover_Enemy_Yadokari(Position, Level);
}
