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
    CVector diff_quake;
    int quake_duration;
    bool isExplode;

public:
    CAnchor();

    void setPosition(CVector newPos);
    inline void setScrollLimit(CVector mapSize) {
        ScrollLimit = mapSize * 32 + CVector(0, 0);
    }   //マップの大きさを整数値で
    inline CVector getAnchoredPosition(CVector pos) {
        if (isAbsolute)return pos;
        return pos - position;
    }
    inline CVector getWorldPosition(CVector pos) {
        return pos + position;
    }
    inline double getAnchorX() {
        if (isAbsolute)return 0.0;
        if (isExplode && quake_duration > 0)return position.x + diff_quake.x;
        return position.x;
    }
    inline double getAnchorY() {
        if (isAbsolute)return 0.0;
        if (isExplode && quake_duration > 0)return position.y + diff_quake.y;
        return position.y;
    }
    inline void Move(CVector diff) {
        setPosition(position + diff);
    }
    inline void Quake(int duraiton) {
        if (duraiton > quake_duration)quake_duration = duraiton;
    }
    void Update();

    inline void enableAbsolute() {
        isAbsolute = true;
    }
    inline void disableAbsolute() {
        isAbsolute = false;
    }
};

