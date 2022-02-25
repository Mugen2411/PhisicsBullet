#pragma once
#include "CField.h"

class CField_Grass :
    public CField
{
    int decoration;
    double animCount;

public:
    CField_Grass(std::string gid, CVector position);
    void Update();
    void Render()const;

    CField* Clone(CVector position);

    void Save(std::ofstream& fout);
};

