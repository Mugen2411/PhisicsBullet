#pragma once
#include "CField.h"

class CField_Grass :
    public CField
{
    int decoration;
public:
    CField_Grass(std::string gid, CVector position);
    void Update();
    void Render()const;

    void Save(std::ofstream& fout);
};

