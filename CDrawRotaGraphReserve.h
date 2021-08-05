#pragma once
#include "IRenderReserve.h"
class CDrawRotaGraphReserve :
    public IRenderReserve
{
protected:
    int x, y;
    float angle, extend;
public:
    CDrawRotaGraphReserve(int GHandle, double Priority, int x, int y, float angle, float extend);
    void Render()const;
};

