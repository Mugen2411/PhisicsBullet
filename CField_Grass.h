#pragma once
#include "CField.h"

class CField_Grass :
    public CField
{
public:
    CField_Grass(const char* gid, CVector position);
    void Update();
    void Render()const;
};

