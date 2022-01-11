#pragma once
#include "CMover.h"
#include "CStatus.h"
#include "CAttribute.h"

class CMover_EnemyBase :
    public CMover
{
public:
    CMover_EnemyBase(int Level, double atkCF, double defCF, double hpCF, CAttribute attrDEF, int baseMoney, int color, CVector Position, double accel, double maxSpeed);
    virtual ~CMover_EnemyBase() {}

    int state = -1; //-1:出現中, 0:棒立ち, 1:移動, 2:怯み, それ以降は敵ごとに定義

    double Accel;
    double MaxSpeed;
    int baseMoney;

    int Direction;
    double animCount;

    CStatus baseParams;		//基礎ステータス(HP・攻撃力・防御力)
    CAttribute attrDEF;		//属性耐性(なんかいっぱい)

    int Color;
    
    virtual void Walk(CVector destination);
    virtual int Update() = 0;
    virtual void Render()const = 0;
    virtual void Dead();
    virtual void Disappear();
    void onWall(CVector WallPosition, CVector WallSize, double WallReflectCF);
    
    void Damage(CAttribute shotATK, int style);
    void RatioDamage(CAttribute shotATK, int style);
    void Drop();
    int DamageColor(CAttribute shotATK);
    void HitDispatch(std::shared_ptr<CMover>);
};

