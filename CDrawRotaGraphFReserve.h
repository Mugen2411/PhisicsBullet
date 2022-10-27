#pragma once
#include "IRenderReserve.h"
class CDrawRotaGraphFReserve :
    public IRenderReserve
{
protected:
    float angle, extend;
public:
    CDrawRotaGraphFReserve(int GHandle, double Priority, float x, float y, float angle, float extend, int width, int height);
    void Render()const;
};
