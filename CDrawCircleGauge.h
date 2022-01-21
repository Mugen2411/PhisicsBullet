#pragma once
#include "IRenderReserve.h"
class CDrawCircleGaugeReserve :
    public IRenderReserve
{
    int x, y;
    double ratio;
public:
    CDrawCircleGaugeReserve(int GHandle, double priority, int x, int y, double ratio);

    void Render()const;
};

