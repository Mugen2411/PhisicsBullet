#include "CMover_Enemy_Bud.h"
#include "CImageManager.h"
#include "CMover_Bullet_Corn.h"
#include "CNumberDrawer.h"
#include "CSoundManager.h"

CMover_Enemy_Bud::CMover_Enemy_Bud(CVector position, int Level) :
	CMover_EnemyBase(20, Level, 0.5, 0.8, CAttribute(1.0).FIRE(0.3).FLOWER(2.0).AQUA(0.5), 10, 0xFFFF00, position, 2.7, 1.2, COF(0.8, 0.99, 0.06, 0.1)),
	testDest(0.0, 0.0)
{
}

int CMover_Enemy_Bud::Update()
{
	switch (state) {
	case 0:
		if (cnt % 60 == 0) {
			if (GetRand(5) == 0)findTargetByDistance(8);
				else Find_Route(4);
		}
		if (!route.empty()) {
			Move_on_Route();
		}
		else {
			CVector ppos = med->GetPlayerPosition();
			med->RegisterMover(std::make_shared<CMover_Bullet_Corn>(baseParams, Position, (ppos - Position).getAngle()));
			CSoundManager::getIns().find("pretty_throw")->Play(CSound::PLAYTYPE::PT_BACK);
			cnt = 0;
			state = 1;
			break;
		}
		cnt++;
		animCount += 0.3;
		if (animCount > 4)animCount = 0;
		break;
	case 1:
		if (cnt > 30) {
			state = 0;
			cnt = 0;
			break;
		}
		cnt++;
		break;
	case -1:
		animCount += 0.1;
		if (animCount > 4) {
			state = 0;
			Find_Route(4);
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
