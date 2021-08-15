#pragma once
#include "CEffect.h"
#include "CNumberDrawer.h"

class CEffect_Number :
    public CEffect
{
    double dy;
    int cnt = 0;
    double num;
    int type = 0;
    int style = 0;
public:
    CEffect_Number(CVector position, double num, int type, int Style=0);

    void Update();
    void Render()const;
};

