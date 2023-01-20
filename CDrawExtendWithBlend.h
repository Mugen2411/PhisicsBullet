#pragma once
#include "IRenderReserve.h"
class CDrawExtendWithBlendReserve :
    public IRenderReserve
{
protected:
    float x1, y1, x2, y2;
    int Color, Blendmode, value;
public:
    CDrawExtendWithBlendReserve(int GHandle, double Priority, float x1, float y1, float x2, float y2, int color, int Blendmode, int value);
    void Render()const;
};