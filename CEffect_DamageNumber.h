#pragma once
#include "CEffect.h"
#include "CNumberDrawer.h"

class CEffect_DamageNumber :
    public CEffect
{
    double dy;
    int cnt = 0;
    double num;
    int type = 0;
    int style = 0;

    CNumberDrawer CND;
public:
    CEffect_DamageNumber(CVector position, double num, int type, int Style=0);

    void Update();
    void Render()const;
};

