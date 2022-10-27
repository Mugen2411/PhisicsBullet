#pragma once
#include "CMover.h"
#include "CMover_Enemy.h"
#include "CAttribute.h"
#include "CStatus.h"

class CMover_ShotBase :
    public CMover
{
protected:
    CAttribute ATK;
    double baseATK;

    std::weak_ptr<CMover> target;

    int cnt;
    int effectColor;
public:
    CMover_ShotBase(double baseATK, CAttribute atk, CVector position, double size, CVector velocity, double mass, COF cofs, int effectColor);

    void BaseUpdate();
    bool BaseRender()const;
    virtual int Update() = 0;
    virtual void Render()const = 0;

    virtual void Dead();            //‘¼ŽE
    virtual void Disappear();       //Ž©ŽE

    void Damage(CAttribute shotATK, int style);
    void RatioDamage(CAttribute shotATK, int style);

    CVector getHomingAngle(double maxSpeed);
    inline void HitDispatch(std::shared_ptr<CMover> m) {
        m->Hit(this);
    }
    void Hit(CMover_EnemyBase*);

    virtual void ifonWall();
};

