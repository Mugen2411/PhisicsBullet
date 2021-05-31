#pragma once
#include "CMover.h"
class CMover_BulletBase :
    public CMover
{
public:
    CMover_BulletBase(CVector position, CVector velocity);

    virtual int Update() = 0;
    virtual void Render()const = 0;

    virtual void Dead() = 0;            //���E
    virtual void Disappear() = 0;       //���E

    virtual void ifonWall() = 0;        //�ǂɏ���Ă�����ǂ����邩
};

