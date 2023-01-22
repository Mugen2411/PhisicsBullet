#pragma once
#include "CAttribute.h"
#include "CImageManager.h"
#include "CMover.h"
#include "CMover_Player.h"
#include "CStatus.h"

class CField;

class CMover_BulletBase : public CMover {
 protected:
  CAttribute atk_;
  CStatus base_params_;
  int color_;

 public:
  CMover_BulletBase(CStatus baseparams, CAttribute atk, CVector position_,
                    double size, CVector velocity, double mass, COF cofs,
                    int color);

  void BaseUpdate();
  bool BaseRender() const;
  virtual int Update() = 0;
  virtual void Render() const = 0;

  virtual void Dead();       //‘¼ŽE
  virtual void Disappear();  //Ž©ŽE

  CAttribute GetBaseAttribute() { return atk_; }
  void Damage(CAttribute shotATK, int style);
  void RatioDamage(CAttribute shotATK, int style);
  CAttribute TestDamage(CAttribute shotATK) { return CAttribute(0.0); }

  inline void HitDispatch(std::shared_ptr<CMover> m) { m->Hit(this); }
  virtual void FieldDispatch(CField* f);

  void Hit(CMover_Player* m);
};
