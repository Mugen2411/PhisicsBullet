#pragma once
#include "CField.h"
#include "CMover_ShotBase.h"
#include "CMover_BulletBase.h"

class CField_Grass :
    public CField
{
    int decoration;
    double animCount;

    int state;
    int BurningTime;

public:
    CField_Grass(std::string gid, CVector position);
    void Update();
    void Render()const;

    void attributeReaction(CAttribute a) {
        a *= CAttribute(0.0).FIRE(1.0);
        Temperature += a.Sum();
    };

    CField* Clone(CVector position);

    void Save(std::ofstream& fout);
};

