#pragma once
#include "CEffect.h"
#include "CNumberDrawer.h"

class CEffect_DamageNumber :
    public CEffect
{
    int cnt = 0;
    int num;
    int type = 0;
public:
    CEffect_DamageNumber(CVector position, int num, int type);

    void Update();
    void Render()const;
};

