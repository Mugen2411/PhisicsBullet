#pragma once
#include "Singleton.h"
#include "CVector.h"

class CAnchor :
    public Singleton<CAnchor>
{
private:
    CVector position;
    bool isAbsolute;
    CVector ScrollLimit;
    CVector diff_explosion;
    int explode_duration;
    bool isExplode;

public:
    CAnchor();

    void setPosition(CVector newPos);
    void setScrollLimit(CVector mapSize);   //�}�b�v�̑傫���𐮐��l��
    CVector getAnchoredPosition(CVector pos);
    CVector getWorldPosition(CVector pos);
    double getAnchorX();
    double getAnchorY();
    void Move(CVector diff);
    void Explosion(int duraiton);
    void Update();

    void enableAbsolute();
    void disableAbsolute();
};

