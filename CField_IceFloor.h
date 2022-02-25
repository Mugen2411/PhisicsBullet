#pragma once
#include "CField.h"

class CField_IceFloor :
    public CField
{
public:
    CField_IceFloor(std::string gid, CVector position, double temperature);
    void Update();
    void Render()const;

    CField* Clone(CVector position);

    void Save(std::ofstream& fout);
};

