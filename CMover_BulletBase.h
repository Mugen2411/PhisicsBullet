#pragma once
#include "CMover.h"
#include "CImageManager.h"

class CMover_BulletBase :
    public CMover
{
public:
    CMover_BulletBase(CVector position, double size, CVector velocity, double mass, double frictionCF, double airresCF, double reflectCF);

    virtual int Update() = 0;
    virtual void Render()const = 0;

    virtual void Dead() = 0;            //‘¼ŽE
    virtual void Disappear() = 0;       //Ž©ŽE

    void Dispatch(std::shared_ptr<CMover>);
};

