#pragma once
#include "CMover_ShotBase.h"

class CMover_Shot_Swimsuit_iPhone :
    public CMover_ShotBase
{
protected:
    double renderAngle;
public:
    CMover_Shot_Swimsuit_iPhone(double baseATK, CVector position, double angle);

    void Dead();

    int Update();
    void Render()const;
};
