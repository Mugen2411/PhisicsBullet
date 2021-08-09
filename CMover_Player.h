#pragma once
#include "CMover.h"
#include "CControllerFactory.h"

class CMover_Player :
    public CMover
{
protected:
    std::shared_ptr<CSTGInputManager> input;
    double Accel;
    double MaxSpeed;

    int State;
    int Direction;
    double animCount;
public:
    CMover_Player(CVector position, double accel, double maxSpeed);
    ~CMover_Player() {};
    virtual void Walk();
    int Update();
    void Render()const;
    void Dead();
    void Disappear();
    void onWall(CVector WallPosition, CVector WallSize, double WallReflectCF);

    void Dispatch(std::shared_ptr<CMover>);
};

