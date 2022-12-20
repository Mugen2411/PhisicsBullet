#pragma once
#include "CMover_BulletBase.h"
class CMover_Bullet_Corn :
    public CMover_BulletBase
{
public:
    CMover_Bullet_Corn(CStatus baseparams, CVector position, double angle, double speed);
    int Update();
    void Render()const;
};

