#pragma once
#include "CField.h"

class CField_Dirt :
    public CField
{
public:
    CField_Dirt(std::string gid, CVector position);
    void Update();
    void Render()const;

    CField* Clone(CVector position);

    void Save(std::ofstream& fout);
};

