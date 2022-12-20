#include "CMover_Enemy_Yadokari.h"
#include "CImageManager.h"
#include "CMover_Bullet_WaterSplash.h"
#include "CNumberDrawer.h"
#include "CSoundManager.h"

CMover_Enemy_Yadokari::CMover_Enemy_Yadokari(CVector position, int Level) :
	CMover_EnemyBase(40, Level, 1.0, 1.35, CAttribute(1.0).NONE(1.8).AQUA(4.0).THUNDER(0.3).FLOWER(0.4), 25, 0xFF0000, position, 2.0, 1.5, COF(0.7, 0.2, 0.08, 0.1)),
	testDest(0.0, 0.0), focus(0.0)
{
}

int CMover_Enemy_Yadokari::Update()
{
	switch (state) {
	case 0:
		if (cnt % 60 == 0) {
			Find_Route(5);
		}
		if (!route.empty())Move_on_Route();
		else {
			CVector ppos = med->GetPlayerPosition();
			focus = (ppos - Position).getAngle();
			state = 1;
			cnt = 0;
			break;
		}
		cnt++;
		animCount += 0.3;
		if (animCount > 4)animCount = 0;
		break;
	case 1:
		if (cnt == 25) {
			for (int i = 0; i < 3; i++) {
				med->RegisterMover(std::make_shared<CMover_Bullet_WaterSplash>(baseParams, Position, focus, 6.0 + i * 3.6));
			}
			CSoundManager::getIns().find("splash")->Play(CSound::PLAYTYPE::PT_BACK);
		}
		if (cnt > 60) {
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
			Find_Route(5);
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
		CImageManager::getIns().find("enemy_yadokari_intro")->DrawRota(Position.x, Position.y, 0.0, 1.0, Constant::priority_enemy, (int)(animCount));
		return;
	}
	CImageManager::getIns().find("enemy_yadokari")->DrawRota(Position.x, Position.y, 0.0, 1.0, Constant::priority_enemy, Direction * 4 + (int)(animCount));
	/*for (auto& i : route) {
		CImageManager::getIns().find("editor_cursor")->DrawRota(i.x, i.y, 0, 1, Constant::priority_enemy);
	}*/
}

CMover_EnemyBase* CMover_Enemy_Yadokari::Clone(CVector Position, int Level)
{
	return new CMover_Enemy_Yadokari(Position, Level);
}
