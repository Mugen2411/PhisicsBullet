#pragma once
#include "CPower.h"
class CPower_Line :
    public CPower
{
protected:
    CVector Position;       //�ʒu
    CVector Direction;      //�p�x�E����
    double Width;           //��
public:
    CPower_Line(CPowerParent* p, CVector position, CVector direction, double width);
};

