#pragma once
#include "IRenderReserve.h"
class CDrawRotaGraphFwithBlendReserve :
    public IRenderReserve
{
protected:
    float x, y;
    float angle, extend;
    int Color, Blendmode, value;
public:
    CDrawRotaGraphFwithBlendReserve(int GHandle, double Priority, float x, float y, float angle, float extend, int color, int Blendmode, int value);
    void Render()const;
};

