#include "CMover_Bullet_Axe.h"

CMover_Bullet_Axe::CMover_Bullet_Axe(CStatus baseparams, CVector position, double angle, double speed)
	:CMover_BulletBase(baseparams, CAttribute(0.0).NONE(60), position, 16, CVector(angle)* speed, 4.0, COF(0.001, 0.05, 0.01, 0.98), 0xFFFFFF),
	baseAngle(0.0)
{
}

int CMover_Bullet_Axe::Update()
{
	baseAngle += Constant::PI2 * Constant::perFrame * 0.8;
	if (Velocity.getLength2() < Constant::bullet_delete_velocity)setStatus(STATUS::DEAD);
	return Status;
}

void CMover_Bullet_Axe::Render() const
{
	CImageManager::getIns().find("bullet_axe")->DrawRota(Position.x, Position.y, Velocity.getAngle() + baseAngle, 1.0, Constant::priority_bullet);
}