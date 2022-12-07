#include "CMover_Enemy_Bud.h"
#include "CImageManager.h"
#include "CMover_Bullet_Corn.h"
#include "CNumberDrawer.h"

CMover_Enemy_Bud::CMover_Enemy_Bud(CVector position, int Level):
	CMover_EnemyBase(20, Level,0.5, 0.8, CAttribute(1.0).FIRE(0.4).FLOWER(2.0), 10, 0xFFFF00, position, 3.0, 2.0, COF(0.1, 0.7, 0.9, 0.0)),
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
			if (auto r = med) {
				CVector ppos = r->GetPlayerPosition();
				if (!!ppos && route.size() <= 4)r->RegisterMover(std::make_shared<CMover_Bullet_Corn>(baseParams, Position, (ppos - Position).getAngle()));

			}
			cnt = 0;
		}
		if(route.size() >= 4)Move_on_Route();
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

void CMover_Enemy_Bud::Render() const
{
	if (state < 0) {
		CImageManager::getIns().find("enemy_bud_intro")->DrawRota(Position.x, Position.y, 0.0, 1.0, Constant::priority_enemy, (int)(animCount));
		return;
	}
	CImageManager::getIns().find("enemy_bud")->DrawRota(Position.x, Position.y, 0.0, 1.0, Constant::priority_enemy, Direction * 4 + (int)(animCount));
	/*for (auto& i : route) {
		CImageManager::getIns().find("editor_cursor")->DrawRota(i.x, i.y, 0, 1, Constant::priority_enemy);
	}*/
}

CMover_EnemyBase* CMover_Enemy_Bud::Clone(CVector Position, int Level)
{
	return new CMover_Enemy_Bud(Position, Level);
}
