#pragma once
#include "CAttribute.h"
#include "CMover.h"
#include "CMover_Enemy.h"
#include "CStatus.h"

class CField;

class CMover_ShotBase : public CMover {
 public:
  CMover_ShotBase(CAttribute baseATK, CAttribute atk, CVector position,
                  double size, CVector velocity, double mass, COF cofs,
                  int effectColor);

  void BaseUpdate();
  bool BaseRender() const;
  virtual int Update() = 0;
  virtual void Render() const = 0;

  virtual void Dead();       //‘¼ŽE
  virtual void Disappear();  //Ž©ŽE

  CAttribute GetBaseAttribute() { return atk_; }

  void Damage(CAttribute shotATK, int style);
  void RatioDamage(CAttribute shotATK, int style);
  CAttribute TestDamage(CAttribute shotATK);

  CVector GetHomingAngle();
  inline void HitDispatch(std::shared_ptr<CMover> m) { m->Hit(this); }
  void Hit(CMover_EnemyBase*);
  virtual void FieldDispatch(CField* f);

  virtual void IfOnWall();

 protected:
  CAttribute atk_;
  CAttribute base_atk_;

  std::weak_ptr<CMover> target_;

  int cnt_;
  int effect_color_;
};
