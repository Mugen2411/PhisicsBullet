#include "CMover_Bullet_Corn.h"

CMover_Bullet_Corn::CMover_Bullet_Corn(CVector position, double angle)
    :CMover_BulletBase(position, 12, CVector(angle)*4.0, 0.5, 5.0, 5.0, 0.1)
{
}

int CMover_Bullet_Corn::Update()
{
    if (Velocity.getLength2() < 0.01)Status = 2;
    return Status;
}

void CMover_Bullet_Corn::Render() const
{
    CImageManager::getIns().find("bullet_bud_corn")->DrawRota(Position.x, Position.y, Velocity.getAngle(), 1.0);
}

void CMover_Bullet_Corn::Dead()
{
}

void CMover_Bullet_Corn::Disappear()
{
}