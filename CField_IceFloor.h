#pragma once
#include "CField.h"

class CField_IceFloor :
    public CField
{
public:
    CField_IceFloor(CVector position);
    void Update();
    void Render()const;
};

