#pragma once
#include "CMover_Enemy.h"

class CMover_Enemy_Bud :
    public CMover_EnemyBase
{
    CVector testDest;
    int cnt = 0;
public:
    CMover_Enemy_Bud(CVector position, int Level);
    int Update();
    void Render()const;
    void Dead();
    void Disappear();
};

