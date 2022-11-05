#pragma once
#include "CCosutumeBase.h"
#include "CMover_Player.h"

class CCostume_Uniform :
    public CCostumeBase
{
public:
    CCostume_Uniform(std::string GID);

    void WeakShot(double baseATK, CVector position, float angle);
    void ChargeShot(double baseATK, CVector position, float angle);

    CCostumeBase* Clone() {
        return new CCostume_Uniform(GID);
    }
};

