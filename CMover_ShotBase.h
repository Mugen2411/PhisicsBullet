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
    CStatus baseParams;
public:
    CMover_ShotBase(CStatus baseparams, CAttribute atk, CVector position, double size, CVector velocity, double mass, double frictionCF, double airresCF, double reflectCF);

    virtual int Update() = 0;
    virtual void Render()const = 0;

    virtual void Dead() = 0;            //‘¼ŽE
    virtual void Disappear() = 0;       //Ž©ŽE

    void Dispatch(std::shared_ptr<CMover>);
    void Hit(CMover_EnemyBase*);
};

