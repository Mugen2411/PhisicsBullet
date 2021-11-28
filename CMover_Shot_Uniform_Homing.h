#pragma once
#include "CMover_ShotBase.h"

class CMover_Shot_Uniform_Homing :
    public CMover_ShotBase
{
protected:
    int cnt;
    double pow;
public:
    CMover_Shot_Uniform_Homing(double baseATK, CVector position, double angle);

    int Update();
    void Render()const;
};