#pragma once
#include "CPower.h"
class CPower_Line :
    public CPower
{
protected:
    CVector Position;       //位置
    CVector Direction;      //角度・長さ
    double Width;           //幅
public:
    CPower_Line(CPowerParent* p, CVector position, CVector direction, double width);
};

