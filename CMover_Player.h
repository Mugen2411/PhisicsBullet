#pragma once
#include "CAttribute.h"
#include "CControllerFactory.h"
#include "CCosutumeBase.h"
#include "CMover.h"
#include "CNumberDrawer.h"
#include "CPassiveSkill.h"
#include "CPowerParent.h"
#include "CStatus.h"
#include "CAnimationCounter.h"

class CField;

class CMover_Player : public CMover {
 public:
  std::shared_ptr<CCostumeBase> costume_;
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
  void OnWall(CField* f, double WallReflectCF);

  void Wait(int duration);
  void Damage(CAttribute BulletATK, int style);
  void RatioDamage(CAttribute BulletATK, int style);
  void RatioHeal();
  void inline HitDispatch(std::shared_ptr<CMover> m) { m->Hit(this); }
  CAttribute TestDamage(CAttribute shotATK) {
    return shotATK / costume_->attribute_def_;
  }
  int DamageColor(CAttribute shotATK);
  void RegisterShot(std::shared_ptr<CMover_ShotBase>);
  void RegisterPower(std::shared_ptr<CPower>);
  void ChangeCostume(CCostumeBase* c) {
    costume_.reset(c);
    costume_->SetPlayer(this);
    cofs_ = costume_->cofs_;
    mass_ = costume_->mass_;
    animCnt_ = CAnimationCounter(4.0, costume_->animation_speed_);
  }
  void ResetCharge() { charge_ = 0.0; }
  void ReduceCharge(double value) { charge_ -= value; }
  double GetHP() { return base_params_.HP_; }

  void Hit(CMover_EnemyBase*);

  virtual void FieldDispatch(CField* f);

 protected:
  std::weak_ptr<CSTGInputManager> input_;

  int state_;  // 0:ëÄçÏâ¬î\ 1:ëÄçÏïsî\
  uint32_t direction_;
  double charge_;  //åªç›ÇÃó≠Çﬂéûä‘(0ÅÖChargeÅÖMaxCharge)
  CAnimationCounter animCnt_;
  CStatus base_params_;
  int digitHP_;
  int wait_duration_;
  int shot_wait_;
  int heal_wait_;

  CNumberDrawer number_drawer_;
};
