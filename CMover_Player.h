#pragma once
#include "CMover.h"
#include "CControllerFactory.h"
#include "CStatus.h"
#include "CAttribute.h"
#include "CCosutumeBase.h"

class CMover_Player :
    public CMover
{
protected:
    std::weak_ptr<CSTGInputManager> input;

    int State;                  //0:����\ 1:����s�\
    int Direction;
    int Charge;					//���݂̗��ߎ���(0��Charge��MaxCharge)
    double animCount;
    CStatus baseParams;
    int waitDuration;

    std::shared_ptr<CCostumeBase> costume;
public:
    CMover_Player(CVector position);
    ~CMover_Player() {};
    virtual void Walk();
    void BaseUpdate();
    int Update();
    void Shot();
    void Render()const;
    void Dead();
    void Disappear();
    void onWall(CVector WallPosition, CVector WallSize, double WallReflectCF);

    void Wait(int duration);
    void Damage(CAttribute BulletATK, int style);
    void RatioDamage(CAttribute BulletATK, int style);
    void HitDispatch(std::shared_ptr<CMover>);
    int DamageColor(CAttribute shotATK);

    void Hit(CMover_EnemyBase*);
};

