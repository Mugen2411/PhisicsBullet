#pragma once
#include "CCosutumeBase.h"
#include "CMover_Player.h"

class CCostume_Uniform :
    public CCostumeBase
{
public:
    CCostume_Uniform(CMover_Player* player);

    std::shared_ptr<CMover_ShotBase> WeakShot(double baseATK, CVector position, float angle);
    std::shared_ptr<CMover_ShotBase> ChargeShot(double baseATK, CVector position, float angle);
};

