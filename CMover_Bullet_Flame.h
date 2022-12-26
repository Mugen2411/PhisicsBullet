#pragma once
#include "CMover_BulletBase.h"
class CMover_Bullet_Flame :
    public CMover_BulletBase
{
public:
    CMover_Bullet_Flame(CStatus baseparams, CVector position, double angle, double speed);
    int Update();
    void Render()const;
protected:
    double animCount;
    double baseAngle;
};

