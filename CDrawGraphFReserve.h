#pragma once
#include "IRenderReserve.h"
class CDrawGraphFReserve :
    public IRenderReserve
{
protected:
    float x, y;
public:
    CDrawGraphFReserve(int GHandle, float x, float y, double Priority);
    void Render()const;
};
