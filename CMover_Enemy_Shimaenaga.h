#pragma once
#include "CMover_Enemy.h"
class CMover_Enemy_Shimaenaga :
    public CMover_EnemyBase
{
protected:
    double animCount;
public:
    CMover_Enemy_Shimaenaga(CVector Position, int Level);
    int Update();
    void Render()const;

    CMover_EnemyBase* Clone(CVector Position, int Level);
};

