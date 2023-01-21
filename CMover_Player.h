#pragma once
#include "CAttribute.h"
#include "CControllerFactory.h"
#include "CCosutumeBase.h"
#include "CMover.h"
#include "CNumberDrawer.h"
#include "CPassiveSkill.h"
#include "CPowerParent.h"
#include "CStatus.h"

class CField;

class CMover_Player : public CMover {
 protected:
  std::weak_ptr<CSTGInputManager> input;

  int State;  // 0:ëÄçÏâ¬î\ 1:ëÄçÏïsî\
  uint32_t Direction;
  double Charge;  //åªç›ÇÃó≠Çﬂéûä‘(0ÅÖChargeÅÖMaxCharge)
  double animCount;
  CStatus baseParams;
  int DigitHP;
  int waitDuration;
  int shotWait;
  int healWait;

  CNumberDrawer CND;

 public:
  std::shared_ptr<CCostumeBase> costume;
  CMover_Player(CVector position, int level, CCostumeBase* costume);
  ~CMover_Player(){};
  virtual void Walk();
  void BaseUpdate();
  bool BaseRender() const;
  int Update();
  void Shot();
  void Render() const;
  void Dead();
  void Disappear();
  void onWall(CField* f, double WallReflectCF);

  void Wait(int duration);
  void Damage(CAttribute BulletATK, int style);
  void RatioDamage(CAttribute BulletATK, int style);
  void RatioHeal();
  void inline HitDispatch(std::shared_ptr<CMover> m) { m->Hit(this); }
  CAttribute TestDamage(CAttribute shotATK) {
    return shotATK / costume->AttributeDEF;
  }
  int DamageColor(CAttribute shotATK);
  void RegisterShot(std::shared_ptr<CMover_ShotBase>);
  void RegisterPower(std::shared_ptr<CPower>);
  void ChangeCostume(CCostumeBase* c) {
    costume.reset(c);
    costume->setPlayer(this);
    Cofs = costume->constants;
    Mass = costume->Mass;
  }
  double getHP() { return baseParams.HP; }

  void Hit(CMover_EnemyBase*);

  virtual void FieldDispatch(CField* f);
};
