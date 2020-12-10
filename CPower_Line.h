#pragma once
#include "CPower.h"
class CPower_Line :
    public CPower
{
protected:
    CVector Position;       //à íu
    CVector Direction;      //äpìxÅEí∑Ç≥
    double Width;           //ïù
public:
    CPower_Line(CPowerParent* p, CVector position, CVector direction, double width);
};

