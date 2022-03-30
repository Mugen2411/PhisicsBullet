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
public:
    CMover_ShotBase(double baseATK, CAttribute atk, CVector position, double size, CVector velocity, double mass, double frictionCF, double airresCF, double reflectCF);

    void BaseUpdate();
    virtual int Update() = 0;
    virtual void Render()const = 0;

    virtual void Dead();            //‘¼ŽE
    virtual void Disappear();       //Ž©ŽE

    void Damage(CAttribute shotATK, int style);
    void RatioDamage(CAttribute shotATK, int style);

    CVector getHomingAngle(double maxSpeed);
    void HitDispatch(std::shared_ptr<CMover>);
    void Hit(CMover_EnemyBase*);

    virtual void ifonWall();
};

