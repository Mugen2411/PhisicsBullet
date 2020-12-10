#pragma once
#include "CMover.h"
class CMover_TestBullet :
    public CMover
{
public:
    CMover_TestBullet(CVector position, CVector velocity);
    int Update();
    void Render()const;

    void Dead();
    void Disappear();

    void ifonWall();
};

