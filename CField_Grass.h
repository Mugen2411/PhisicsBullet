#pragma once
#include "CField.h"
class CField_Grass :
    public CField
{
public:
    CField_Grass(CFieldParent* f, CVector position);
    void Update();
    void Render()const;
};

