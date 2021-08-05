#pragma once
#include "IRenderReserve.h"
class CDrawGraphReserve :
    public IRenderReserve
{
protected:
    int x, y;
public:
    CDrawGraphReserve(int GHandle, int x, int y, double Priority);
    void Render()const;
};

