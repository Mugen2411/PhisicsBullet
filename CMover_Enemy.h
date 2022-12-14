#pragma once
#include "CMover.h"
#include "CStatus.h"
#include "CAttribute.h"
#include <random>

class CField;

class CMover_EnemyBase :
    public CMover
{
public:
    CMover_EnemyBase(double Mass, int Level, double atkCF, double hpCF, CAttribute attrDEF, int baseMoney,
        int color, CVector Position, double accel, double maxSpeed, COF cofs);
    virtual ~CMover_EnemyBase() {}

    int state = -1; //-1:oŒ»’†, 0:–_—§‚¿, 1:ˆÚ“®, 2:‹¯‚İ, ‚»‚êˆÈ~‚Í“G‚²‚Æ‚É’è‹`

    double Accel;
    double MaxSpeed;
    int baseMoney;

    int pushed;

    int Direction;
    double animCount;

    CStatus baseParams;		//Šî‘bƒXƒe[ƒ^ƒX(HPEUŒ‚—ÍE–hŒä—Í)
    CAttribute attrDEF;		//‘®«‘Ï«(‚È‚ñ‚©‚¢‚Á‚Ï‚¢)

    int Color;

    std::list<CVector> route;
    
    virtual void Walk(CVector destination);
    virtual void Move_on_Route();
    void Find_Route(int distance);
    void findTargetByDistance(int distance);

    void BaseUpdate();
    bool BaseRender()const;
    virtual int Update() = 0;
    virtual void Render()const = 0;
    virtual void Dead();
    virtual void Disappear();
    void onWall(CField* f, double WallReflectCF);

    void Render_HPGuage()const;
    
    void Damage(CAttribute shotATK, int style);
    void RatioDamage(CAttribute shotATK, int style);
    CAttribute TestDamage(CAttribute shotATK) {
        return shotATK / attrDEF;
    }
    void Drop();
    int DamageColor(CAttribute shotATK);

    virtual void FieldDispatch(CField* f){}

    inline void HitDispatch(std::shared_ptr<CMover> m) {
        m->Hit(this);
    }
    void Hit(CMover_EnemyBase*);
    void Hit(CMover_Player*);

    virtual CMover_EnemyBase* Clone(CVector Position, int Level) = 0;

protected:
    std::random_device seed;
    std::default_random_engine rand;
};

