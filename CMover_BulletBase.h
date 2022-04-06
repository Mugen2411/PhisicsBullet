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
        COF cofs);

    void BaseUpdate();
    bool BaseRender()const;
    virtual int Update() = 0;
    virtual void Render()const = 0;

    virtual void Dead();            //‘¼ŽE
    virtual void Disappear();       //Ž©ŽE

    void Damage(CAttribute shotATK, int style);
    void RatioDamage(CAttribute shotATK, int style);

    inline void HitDispatch(std::shared_ptr<CMover> m) {
        m->Hit(this);
    }

    void Hit(CMover_Player* m);
};

