#pragma once
#include "CEffect.h"
class CEffect_MoneyNumber :
    public CEffect
{
    int num;
    double dy;
    int cnt;
public:
    CEffect_MoneyNumber(CVector position, int num);

    void Update();
    void Render()const;
};

