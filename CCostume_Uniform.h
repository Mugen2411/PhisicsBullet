#pragma once
#include "CCosutumeBase.h"
#include "CMover_Player.h"

class CCostume_Uniform :
    public CCostumeBase
{
public:
    CCostume_Uniform(CMover_Player* player);

    void WeakShot(double baseATK, CVector position, float angle);
    void ChargeShot(double baseATK, CVector position, float angle);

    CCostumeBase* Clone(CMover_Player* player) {
        return new CCostume_Uniform(player);
    }
};

