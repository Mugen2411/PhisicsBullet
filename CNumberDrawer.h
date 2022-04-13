#pragma once
class CNumberDrawer
{
    const int Xnum;
public:
    CNumberDrawer();
    void Draw(int x, int y, double num, int type, int style, double priority)const;
    void Draw(int x, int y, int num, int type, int style, double priority)const;
};

