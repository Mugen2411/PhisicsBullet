#pragma once
#include "CMover_Enemy.h"

class CMover_Enemy_Acecorn :
    public CMover_EnemyBase
{
    CVector testDest;
    int cnt = 0;
    float focus;
public:
    CMover_Enemy_Acecorn(CVector position, int Level);
    int Update();
    void Render()const;

    CMover_EnemyBase* Clone(CVector Position, int Level);
};

