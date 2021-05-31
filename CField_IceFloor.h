#pragma once
#include "CField.h"

class CField_IceFloor :
    public CField
{
public:
    CField_IceFloor(const char* gid, CVector position, double temperature);
    void Update();
    void Render()const;
};

