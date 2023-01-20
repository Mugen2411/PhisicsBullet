#pragma once
#include "CPower.h"
class CPower_Line :
    public CPower
{
protected:
    CVector Direction;      //�p�x�E����
    double Width;           //��
    CVector Corner[4];      //�l��
    CVector ForceDirection; //�͂����������

public:
    CPower_Line(CVector position, CVector direction, double width, double power, int duration);
    bool isHit(CVector mPosition, double size);
    void ApplyForceToMover(CMover*);
    int Update();
    void Render()const;
};

