#include "CMover_BulletBase.h"

#include <DxLib.h>

#include "CAnchor.h"
#include "CEffectParent.h"
#include "CEffect_BulletDelete.h"
#include "CEffect_DamageNumber.h"
#include "CField.h"
#include "CImageManager.h"

CMover_BulletBase::CMover_BulletBase(CStatus baseparams, CAttribute atk,
                                     CVector position_, double size,
                                     CVector velocity, double mass, COF cofs,
                                     int color = 0xFFFFFF)
    : CMover(kBullet, position_, size, velocity, mass, cofs, 0),
      base_params_(baseparams),
      atk_(atk),
      color_(color) {}

void CMover_BulletBase::BaseUpdate() {}

bool CMover_BulletBase::BaseRender() const {
  auto p = CAnchor::GetIns().GetAnchoredPosition(position_);
  if (p.x_ + size_ > 0 && p.x_ - size_ < Constant::kScreenW && p.y_ + size_ > 0 &&
      p.y_ - size_ < Constant::kScreenH)
    return true;
  return false;
}

void CMover_BulletBase::Dead() {
  CEffectParent::RegisterEffect(
      std::make_shared<CEffect_BulletDelete>(position_, velocity_, size_, color_));
}

void CMover_BulletBase::Disappear() {}

void CMover_BulletBase::Damage(CAttribute shotATK, int style) {}

void CMover_BulletBase::RatioDamage(CAttribute shotATK, int style) {}

void CMover_BulletBase::Hit(CMover_Player* m) {
  m->Damage(atk_ * base_params_.atk_, 0);
  m->ApplyForce(velocity_ * mass_);
  SetStatus(Status::kDead);
  CAnchor::GetIns().Quake(2);
}

void CMover_BulletBase::FieldDispatch(CField* f) { f->AttributeEffect(this); }