#pragma once
#include "Calc/CAttribute.h"
#include "Graphic/Image/CImageManager.h"
#include "Mover/CMover.h"
#include "Mover/CMover_Player.h"
#include "Calc/CStatus.h"

class CField;

class CMover_BulletBase : public CMover {
 protected:
  CAttribute atk_;
  CStatus base_params_;
  int color_;

 public:
  CMover_BulletBase(std::string GID, CStatus baseparams, CVector position,
                    CVector velocity);

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

  void LoadStatus(std::string GID);
};
