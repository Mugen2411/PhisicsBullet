#pragma once
#include "Singleton.h"
class CNumberDrawer :
    public Singleton<CNumberDrawer>
{
public:
    CNumberDrawer();
    void Draw(int x, int y, double num, int type)const;
    void Draw(int x, int y, int num, int type)const;
};

