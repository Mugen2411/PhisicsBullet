#pragma once
#include "CMover.h"
#include "CMover_Enemy.h"
#include "CAttribute.h"
#include "CStatus.h"

class CField;

class CMover_ShotBase :
    public CMover
{
protected:
    CAttribute ATK;
    CAttribute baseATK;

    std::weak_ptr<CMover> target;

    int cnt;
    int effectColor;
public:
    CMover_ShotBase(CAttribute baseATK, CAttribute atk, CVector position, double size, CVector velocity, double mass, COF cofs, int effectColor);

    void BaseUpdate();
    bool BaseRender()const;
    virtual int Update() = 0;
    virtual void Render()const = 0;

    virtual void Dead();            //‘¼ŽE
    virtual void Disappear();       //Ž©ŽE

    CAttribute getBaseAttribute() {
        return ATK;
    }

    void Damage(CAttribute shotATK, int style);
    void RatioDamage(CAttribute shotATK, int style);
    CAttribute TestDamage(CAttribute shotATK);

    CVector getHomingAngle();
    inline void HitDispatch(std::shared_ptr<CMover> m) {
        m->Hit(this);
    }
    void Hit(CMover_EnemyBase*);
    virtual void FieldDispatch(CField* f);

    virtual void ifonWall();
};

