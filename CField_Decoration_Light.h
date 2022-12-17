#pragma once
#include "CField_Wall.h"
#include "CMover_ShotBase.h"
#include "CMover_BulletBase.h"

class CField_Decoration_Light :
    public CField_Wall
{
    int state;
public:
    CField_Decoration_Light(std::string gid, CVector position);

    void Update();
    void Render()const;

    void attributeReaction(CAttribute a) {
        auto f = a * CAttribute(0.0).THUNDER(1.0);
        if (f.Sum() > 0.0) {
            state = 1;
        }
    };
    virtual void attributeEffect(CMover_BulletBase* m) {};

    CField* Clone(CVector position);

};
