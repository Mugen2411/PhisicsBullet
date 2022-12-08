#pragma once
#include "CField.h"

class CField_Wall_PlayerSpawner :
    public CField
{
public:
    CField_Wall_PlayerSpawner(std::string gid, CVector position);
    void Update();
    void Render()const;

    CField* Clone(CVector position);
};