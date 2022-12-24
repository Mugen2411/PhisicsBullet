#pragma once
#include "CMover_ShotBase.h"

class CMover_Shot_Swimsuit_Bat :
    public CMover_ShotBase
{
protected:
    int cnt;
public:
    CMover_Shot_Swimsuit_Bat(CAttribute baseATK, CVector position, double angle, double speed);

    void Dead(){}
    int Update();
    void Render()const;
};
