#pragma once
#include "CMover.h"
class CMover_EnemyBase :
    public CMover
{
public:
    CMover_EnemyBase(int Level, CVector Position, double accel, double maxSpeed);
    virtual ~CMover_EnemyBase() {}

    int Level = 0;
    int state = -1; //-1:�o����, 0:�_����, 1:�ړ�, 2:����, ����ȍ~�͓G���Ƃɒ�`

    double Accel;
    double MaxSpeed;

    double MaxHP;
    double HP;
    double ATK;
    double DEF;

    int Direction;
    double animCount;
    
    virtual void Walk(CVector destination);
    virtual int Update() = 0;
    virtual void Render()const = 0;
    virtual void Dead() = 0;
    virtual void Disappear() = 0;
    void onWall(CVector WallPosition, CVector WallSize, double WallReflectCF);
};

