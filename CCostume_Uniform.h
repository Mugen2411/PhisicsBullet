#pragma once
#include "CCosutumeBase.h"
#include "CMover_Shot_Uniform_Homing.h"

class CCostume_Uniform :
    public CCostumeBase
{
public:
    CCostume_Uniform();

    std::shared_ptr<CMover_ShotBase> WeakShot(double baseATK, CVector position, float angle);
    std::shared_ptr<CMover_ShotBase> ChargeShot(double baseATK, CVector position, float angle);
};

