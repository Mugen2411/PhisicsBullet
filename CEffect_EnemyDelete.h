#pragma once
#include "CEffect.h"
class CEffect_EnemyDelete :
    public CEffect
{
    int cnt = 0;
    double Size;
    int Color;
    double animCount;
    const int duration;
public:
    CEffect_EnemyDelete(CVector position, double size, int color);

    void Update();
    void Render()const;
};

