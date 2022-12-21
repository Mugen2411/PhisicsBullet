#include "CMover_Enemy_Goblin.h"
#include "CImageManager.h"
#include "CMover_Bullet_Axe.h"
#include "CNumberDrawer.h"
#include "CSoundManager.h"
#include "CEffect_Bright.h"

CMover_Enemy_Goblin::CMover_Enemy_Goblin(CVector position, int Level) :
	CMover_EnemyBase(40, Level, 1.0, 1.5, CAttribute(1.0).NONE(0.5).FIRE(2.5).THUNDER(0.8), 40, 0x00FF00, position, 2.5, 1.2, COF(0.8, 0.9, 0.03, 0.1)),
	testDest(0.0, 0.0), focus(0.0)
{
}

int CMover_Enemy_Goblin::Update()
{
	switch (state) {
	case 0:
		if (cnt % 80 == 0) {
			Find_Route(6);
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
		animCount += 0.2;
		if (animCount > 4)animCount = 0;
		break;
	case 1:
		if (cnt == 32) {
			med->RegisterMover(std::make_shared<CMover_Bullet_Axe>(baseParams, Position, focus, 6.0));
			CSoundManager::getIns().find("throw")->Play(CSound::PLAYTYPE::PT_BACK);
		}
		if (cnt > 80) {
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
			Find_Route(6);
			animCount = 0;
			cnt = 0;
		}
		break;
	}
	return Status;
}

void CMover_Enemy_Goblin::Render() const
{

	if (state < 0) {
		CImageManager::getIns().find("enemy_goblin_intro")->DrawRota(Position.x, Position.y, 0.0, 1.0, Constant::priority_enemy, (int)(animCount));
		return;
	}
	CImageManager::getIns().find("enemy_goblin")->DrawRota(Position.x, Position.y, 0.0, 1.0, Constant::priority_enemy, Direction * 4 + (int)(animCount));
	CEffect_Bright::getIns().Register(CEffect_Bright::BrightDesc(Position, 192, 192));
}

CMover_EnemyBase* CMover_Enemy_Goblin::Clone(CVector Position, int Level)
{
	return new CMover_Enemy_Goblin(Position, Level);
}
