#pragma once
#include "IRenderReserve.h"
class CDrawRotaGraphFReserve :
    public IRenderReserve
{
protected:
    float x, y;
    float angle, extend;
public:
    CDrawRotaGraphFReserve(int GHandle, double Priority, float x, float y, float angle, float extend);
    void Render()const;
};
