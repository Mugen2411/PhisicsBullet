#pragma once
#include "CPower.h"
class CPower_Line :
    public CPower
{
protected:
    CVector Direction;      //Šp“xE’·‚³
    double Width;           //•
    CVector Corner[4];      //l‹÷
    CVector ForceDirection; //—Í‚ğ‚©‚¯‚é•ûŒü

public:
    CPower_Line(CVector position, CVector direction, double width, double power, int duration);
    bool isHit(CVector mPosition, double size);
    void ApplyForceToMover(CMover*);
    int Update();
    void Render()const;
};

