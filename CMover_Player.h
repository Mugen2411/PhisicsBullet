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
    std::shared_ptr<CSTGInputManager> input;

    int State;
    int Direction;
    int Charge;					//åªç›ÇÃó≠Çﬂéûä‘(0ÅÖChargeÅÖMaxCharge)
    double animCount;
    CStatus baseParams;

    std::shared_ptr<CCostumeBase> costume;
public:
    CMover_Player(CVector position);
    ~CMover_Player() {};
    virtual void Walk();
    int Update();
    void Shot();
    void Render()const;
    void Dead();
    void Disappear();
    void onWall(CVector WallPosition, CVector WallSize, double WallReflectCF);

    void Damage(CAttribute BulletATK, int style);
    void HitDispatch(std::shared_ptr<CMover>);
    int DamageColor(CAttribute shotATK);
};

