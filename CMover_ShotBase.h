#pragma once
#include "CAttribute.h"
#include "CMover.h"
#include "CMover_Enemy.h"
#include "CStatus.h"
#include "CDataLoader.h"

class CField;

class CMover_ShotBase : public CMover {
 public:
  CMover_ShotBase(std::string GID, CAttribute baseATK, CVector position, CVector velocity);

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

  std::string gid_;

  void LoadStatus();
};
