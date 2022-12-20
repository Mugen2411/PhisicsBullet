#pragma once
#include "CEffect.h"
class CEffect_EnemyDelete :
    public CEffect
{
    int cnt = 0;
    double Size;
    int Color;
    double animCount;
    int duration;
public:
    CEffect_EnemyDelete(CVector position, double size, int color, int duration);

    void Update();
    void Render()const;
};

