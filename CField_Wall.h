#pragma once
#include "CField.h"

class CField_Wall :
    public CField
{
public:
    CField_Wall(std::string GID, CVector position, COF cofs);

    void Hit(CMover*)override;
};

