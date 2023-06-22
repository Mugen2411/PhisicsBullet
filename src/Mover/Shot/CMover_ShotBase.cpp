#include "CMover_ShotBase.h"

#include "Graphic/CAnchor.h"
#include "Effect/CEffectParent.h"
#include "Effect/CEffect_BulletDelete.h"
#include "Effect/CEffect_DamageNumber.h"
#include "Field/CField.h"

CMover_ShotBase::CMover_ShotBase(std::string GID, CAttribute baseATK,
                                 CVector position, CVector velocity)
    : CMover(kShot, position, 0, velocity, 0, COF(), 0),
      atk_(0),
      base_atk_(baseATK),
      cnt_(0),
      effect_color_(0),
      gid_(GID) {
  LoadStatus();
}

void CMover_ShotBase::BaseUpdate() { cnt_++; }

bool CMover_ShotBase::BaseRender() const {
  auto p = CAnchor::GetIns().GetAnchoredPosition(position_);
  if (p.x_ + size_ > 0 && p.x_ - size_ < Constant::kScreenW &&
      p.y_ + size_ > 0 && p.y_ - size_ < Constant::kScreenH)
    return true;
  return false;
}

void CMover_ShotBase::Dead() {
  CEffectParent::RegisterEffect(std::make_shared<CEffect_BulletDelete>(
      position_, velocity_, size_ * 2, effect_color_));
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
  auto diff =
      (target_.lock()->GetPosition() - (position_ + velocity_)).GetNorm();

  return diff;
}

void CMover_ShotBase::Hit(CMover_EnemyBase* m) {
  m->Damage(atk_ * base_atk_, 1);
  m->ApplyForce(velocity_ * mass_);
  SetStatus(Status::kDead);
}

void CMover_ShotBase::IfOnWall() { SetStatus(Status::kDead); }

void CMover_ShotBase::LoadStatus() {
  auto c = CDataLoader::GetIns().Get("main")->GetChild("shot")->GetChild(gid_);
  mass_ = c->GetChild("mass")->GetInt();
  cofs_.Load(c->GetChild("cof"));
  atk_.Load(c->GetChild("atk"));
  effect_color_ = c->GetChild("effc")->GetInt();
  size_ = ceil(c->GetChild("size")->GetInt() / 2);
}

void CMover_ShotBase::FieldDispatch(CField* f) { f->AttributeEffect(this); }
