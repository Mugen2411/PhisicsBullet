#include "CMover_Bullet_Corn.h"

CMover_Bullet_Corn::CMover_Bullet_Corn(CStatus baseparams, CVector position, double angle)
    :CMover_BulletBase(baseparams, CAttribute(0.0).NONE(50).FLOWER(50), position, 16, CVector(angle) * 4.0, 0.5, COF(0.001, 0.3, 0.03, 0.1), 0xFFFF00)
{
}

int CMover_Bullet_Corn::Update()
{
    if (Velocity.getLength2() < 0.05)Status = 2;
    return Status;
}

void CMover_Bullet_Corn::Render() const
{
    CImageManager::getIns().find("bullet_bud_corn")->DrawRota(Position.x, Position.y, Velocity.getAngle(), 1.0, Constant::priority_bullet);
}