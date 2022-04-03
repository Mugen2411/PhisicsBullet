#pragma once
#include "CMover.h"
#include "CImageManager.h"
#include "CMover_Player.h"
#include "CStatus.h"
#include "CAttribute.h"

class CMover_BulletBase :
    public CMover
{
protected:
    CAttribute ATK;
    CStatus baseParams;
public:
    CMover_BulletBase(CStatus baseparams, CAttribute atk, CVector position, double size, CVector velocity, double mass, 
        double frictionCF, double airresCF, double waterresCF, double reflectCF);

    void BaseUpdate();
    virtual int Update() = 0;
    virtual void Render()const = 0;

    virtual void Dead();            //‘¼ŽE
    virtual void Disappear();       //Ž©ŽE

    void Damage(CAttribute shotATK, int style);
    void RatioDamage(CAttribute shotATK, int style);

    void HitDispatch(std::shared_ptr<CMover>);

    void Hit(CMover_Player* m);
};

