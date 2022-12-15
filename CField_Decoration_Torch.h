#pragma once
#include "CField_Wall.h"
#include "CMover_ShotBase.h"
#include "CMover_BulletBase.h"

class CField_Decoration_Torch :
    public CField_Wall
{
    double animCount;
    int state;
    int BurningTime;
public:
    CField_Decoration_Torch(std::string gid, CVector position);

    void Update();
    void Render()const;

    void attributeReaction(CAttribute a) {
        auto f = a * CAttribute(0.0).FIRE(1.0);
        if (f.Sum() > 0.0) {
            state = 1;
        }
        auto aq = a * CAttribute(0.0).AQUA(1.0);
        if (aq.Sum() > 0.0) {
            state = 0;
        }
    };
    virtual void attributeEffect(CMover_BulletBase* m) {};

    CField* Clone(CVector position);

};
