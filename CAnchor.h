#pragma once
#include "Singleton.h"
#include "CVector.h"

class CAnchor :
    public Singleton<CAnchor>
{
private:
    CVector position;
    bool isAbsolute;

public:
    CAnchor();

    void setPosition(CVector newPos);
    CVector getAnchoredPosition(CVector pos);
    CVector getWorldPosition(CVector pos);
    double getAnchorX();
    double getAnchorY();

    void enableAbsolute();
    void disableAbsolute();
};

