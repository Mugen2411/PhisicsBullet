#pragma once
#include "CMover.h"
class CMover_BulletBase :
    public CMover
{
public:
    CMover_BulletBase(CVector position, CVector velocity);

    virtual int Update() = 0;
    virtual void Render()const = 0;

    virtual void Dead() = 0;            //他殺
    virtual void Disappear() = 0;       //自殺

    virtual void ifonWall() = 0;        //壁に乗っていたらどうするか
};

