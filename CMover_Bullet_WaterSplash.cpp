#include "CMover_Bullet_WaterSplash.h"

CMover_Bullet_WaterSplash::CMover_Bullet_WaterSplash(CStatus baseparams, CVector position, double angle, double speed)
    :CMover_BulletBase(baseparams, CAttribute(0.0).NONE(20).AQUA(90), position, 16, CVector(angle) * speed, 0.8, COF(0.002, 0.001, 0.1, 0.1), 0x00FFFF)
{
}

int CMover_Bullet_WaterSplash::Update()
{
    if (Velocity.getLength2() < 0.05)Status = 2;
    return Status;
}

void CMover_Bullet_WaterSplash::Render() const
{
    CImageManager::getIns().find("bullet_yadokari_watersplash")->DrawRota(Position.x, Position.y, Velocity.getAngle(), 1.0, Constant::priority_bullet);
}