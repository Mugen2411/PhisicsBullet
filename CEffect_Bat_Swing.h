#pragma once
#include "CEffect.h"
class CEffect_Bat_Swing :
    public CEffect
{
    double angle;
    int cnt = 0;
    int Color;
public:
    CEffect_Bat_Swing(CVector position, double angle);

    void Update();
    void Render()const;
};

