#pragma once
#include "Singleton.h"
class CNumberDrawer :
    public Singleton<CNumberDrawer>
{
public:
    CNumberDrawer();
    const void Draw(int x, int y, int num, int type);
};

