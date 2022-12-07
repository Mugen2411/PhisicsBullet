#include "CMover_Enemy_Shimaenaga.h"
#include "CImageManager.h"

CMover_Enemy_Shimaenaga::CMover_Enemy_Shimaenaga(CVector Position, int Level):
	CMover_EnemyBase(40, Level, 0.1, 3.0, CAttribute(0.6), 200, 0xFFFFFF, Position, 0.0, 0.0, COF(0.1, 0.8, 0.8, 0.0)), animCount(0.0)
{
}

int CMover_Enemy_Shimaenaga::Update()
{
	animCount += 0.1;
	if (animCount > 3)animCount = 0.0;
	return Status;
}

void CMover_Enemy_Shimaenaga::Render() const
{
	CImageManager::getIns().find("enemy_shimaenaga")->DrawRota(Position.x, Position.y, 0.0, 1.0, Constant::priority_enemy, animCount);
}

CMover_EnemyBase* CMover_Enemy_Shimaenaga::Clone(CVector Position, int Level)
{
	return new CMover_Enemy_Shimaenaga(Position, Level);
}
