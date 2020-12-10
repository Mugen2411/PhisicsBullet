#pragma once
#include "CField.h"
class CField_Wall :
    public CField
{
public:
    CField_Wall(CFieldParent* f, CVector size, double frictionCF, double temperature);

    void setFrictionForce(CMover*)override;
    void Update();
    void Render()const;

    void Hit(CMover*)override;
};

