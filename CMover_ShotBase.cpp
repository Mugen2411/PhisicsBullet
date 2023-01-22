#include "CMover_ShotBase.h"

#include "CAnchor.h"
#include "CEffectParent.h"
#include "CEffect_BulletDelete.h"
#include "CEffect_DamageNumber.h"
#include "CField.h"

CMover_ShotBase::CMover_ShotBase(CAttribute baseATK, CAttribute atk,
                                 CVector position, double size,
                                 CVector velocity, double mass, COF cofs,
                                 int effectColor = 0xFFFFFF)
    : CMover(kShot, position, size, velocity, mass, cofs, 0),
      atk_(atk),
      base_atk_(baseATK),
      cnt_(0),
      effect_color_(effectColor) {}

void CMover_ShotBase::BaseUpdate() { cnt_++; }

bool CMover_ShotBase::BaseRender() const {
  auto p = CAnchor::GetIns().GetAnchoredPosition(position_);
  if (p.x + size_ > 0 && p.x - size_ < Constant::kScreenW && p.y + size_ > 0 &&
      p.y - size_ < Constant::kScreenH)
    return true;
  return false;
}

void CMover_ShotBase::Dead() {
  CEffectParent::RegisterEffect(std::make_shared<CEffect_BulletDelete>(
      position_, velocity_, size_, effect_color_));
}

void CMover_ShotBase::Disappear() {}

void CMover_ShotBase::Damage(CAttribute shotATK, int style) {}

void CMover_ShotBase::RatioDamage(CAttribute shotATK, int style) {}

CAttribute CMover_ShotBase::TestDamage(CAttribute shotATK) {
  return CAttribute(0.0);
}

CVector CMover_ShotBase::GetHomingAngle() {
  if (!target_.lock()) {
    target_ = med_->GetNearestMover(CMover::MoverID::kEnemy, position_);
    return CVector(0.0, 0.0);
  }
  auto diff = (target_.lock()->GetPosition() - (position_ + velocity_)).GetNorm();

  return diff;
}

void CMover_ShotBase::Hit(CMover_EnemyBase* m) {
  m->Damage(atk_ * base_atk_, 1);
  m->ApplyForce(velocity_ * mass_);
  SetStatus(Status::kDead);
}

void CMover_ShotBase::IfOnWall() { SetStatus(Status::kDead); }

void CMover_ShotBase::FieldDispatch(CField* f) { f->AttributeEffect(this); }
