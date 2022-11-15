#pragma once
#include "CField.h"
#include "CNumberDrawer.h"

class CField_Wall_EnemySpawner :
    public CField
{
    int index;
    CNumberDrawer CND;
public:
    CField_Wall_EnemySpawner(std::string gid, CVector position, int index);
    void Update();
    void Render()const;

    CField* Clone(CVector position);
};