#include "CMover_Enemy_Shimaenaga.h"
#include "CImageManager.h"

CMover_Enemy_Shimaenaga::CMover_Enemy_Shimaenaga(CVector Position, int Level):
	CMover_EnemyBase(40, Level, 0.1, 5.0, 5.0, CAttribute(1.0), 1000, 0xFFFFFF, Position, 0.0, 0.0), animCount(0.0)
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
	CImageManager::getIns().find("enemy_shimaenaga")->DrawRota(Position.x, Position.y, 0.0, 1.0, 0.0, animCount);
	Render_HPGuage();
}
