#pragma once
#include "CEffect.h"
#include "CNumberDrawer.h"

class CEffect_DamageNumber :
    public CEffect
{
    int cnt = 0;
    double num;
    int type = 0;
public:
    CEffect_DamageNumber(CVector position, double num, int type);

    void Update();
    void Render()const;
};

