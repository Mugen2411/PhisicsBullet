#pragma once
#include "CField_Wall.h"
class CField_Wall_Log :
    public CField_Wall
{
    double animCount;
    int state;
    int BurningTime;
public:
    //state = 0:�� 1:���㒆 2:�ł�
    CField_Wall_Log(std::string gid, CVector position, int state);

    void Update();
    void Render()const;

    CField* Clone(CVector position);
   
};

