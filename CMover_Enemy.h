#pragma once
#include "CMover.h"
#include "CStatus.h"
#include "CAttribute.h"

class CMover_EnemyBase :
    public CMover
{
public:
    CMover_EnemyBase(int Level, CAttribute attrDEF, int baseMoney, int color, CVector Position, double accel, double maxSpeed);
    virtual ~CMover_EnemyBase() {}

    int state = -1; //-1:�o����, 0:�_����, 1:�ړ�, 2:����, ����ȍ~�͓G���Ƃɒ�`

    double Accel;
    double MaxSpeed;
    int baseMoney;

    CStatus baseParams;
    CAttribute attrDEF;

    int Direction;
    double animCount;

    int Color;
    
    virtual void Walk(CVector destination);
    virtual int Update() = 0;
    virtual void Render()const = 0;
    virtual void Dead();
    virtual void Disappear();
    void onWall(CVector WallPosition, CVector WallSize, double WallReflectCF);
    
    double Damage(CAttribute shotATK);
    void Drop();
    int DamageColor(CAttribute shotATK);
    void Dispatch(std::shared_ptr<CMover>);
};

