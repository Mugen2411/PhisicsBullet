#include "CMover_Bullet_Flame.h"

CMover_Bullet_Flame::CMover_Bullet_Flame(CStatus baseparams, CVector position, double angle, double speed)
	:CMover_BulletBase(baseparams, CAttribute(0.0).NONE(2).FIRE(18), position, 16, CVector(angle)* speed,
		0.5, COF(0.005, 0.005, 0.04, 0.1), 0xFF0000), baseAngle(0.0), animCount(0.0)
{
}

int CMover_Bullet_Flame::Update()
{
	animCount += 0.25;
	if (animCount > 4.0)animCount = 0;
	baseAngle += Constant::PI2 * 3 * Constant::perFrame;
	if (Velocity.getLength2() < Constant::bullet_delete_velocity)setStatus(STATUS::DEAD);
	return Status;
}

void CMover_Bullet_Flame::Render() const
{
	CImageManager::getIns().find("effect_flame")->DrawRotaFwithBlend(Position.x, Position.y,
		Velocity.getAngle() + baseAngle, 1.0, 0xFFFFFF,
		CImageManager::BLENDMODE::BM_ADD, 0xFF, Constant::priority_bullet, animCount);
}