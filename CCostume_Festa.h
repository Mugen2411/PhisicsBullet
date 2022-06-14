#pragma once
#include "CCosutumeBase.h"
#include "CMover_Player.h"

class CCostume_Festa :
    public CCostumeBase
{
public:
    CCostume_Festa(CMover_Player* player);

    void WeakShot(double baseATK, CVector position, float angle);
    void ChargeShot(double baseATK, CVector position, float angle);
};

