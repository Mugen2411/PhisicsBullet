#pragma once
#include "CMover_ShotBase.h"

class CMover_Shot_Uniform_Homing :
    public CMover_ShotBase
{
protected:
    std::weak_ptr<CMover> target;
    int cnt;
    double pow;
public:
    CMover_Shot_Uniform_Homing(CVector position, float angle);

    int Update();
    void Render()const;
    
    void Dead();
    void Disappear();
};