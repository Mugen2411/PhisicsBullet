#include "CMover_Bullet_Axe.h"

CMover_Bullet_Axe::CMover_Bullet_Axe(CStatus baseparams, CVector position, double angle, double speed)
	:CMover_BulletBase(baseparams, CAttribute(0.0).NONE(80), position, 16, CVector(angle)* speed, 4.0, COF(0.001, 0.1, 0.01, 0.98), 0xFFFFFF),
	baseAngle(0.0)
{
}

int CMover_Bullet_Axe::Update()
{
	baseAngle += Constant::PI2 * Constant::perFrame * 2.0;
	if (Velocity.getLength2() < 0.05)setStatus(STATUS::DEAD);
	return Status;
}

void CMover_Bullet_Axe::Render() const
{
	CImageManager::getIns().find("bullet_axe")->DrawRota(Position.x, Position.y, Velocity.getAngle() + baseAngle, 1.0, Constant::priority_bullet);
}