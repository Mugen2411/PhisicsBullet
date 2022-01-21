#pragma once
#include "CMover_ShotBase.h"

class CMover_Shot_Uniform_StrongMagic :
    public CMover_ShotBase
{
protected:
public:
    CMover_Shot_Uniform_StrongMagic(double baseATK, CVector position, double angle);

    int Update();
    void Render()const;
};
