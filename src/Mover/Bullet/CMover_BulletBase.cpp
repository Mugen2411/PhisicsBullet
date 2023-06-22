#include "CMover_BulletBase.h"

#include <DxLib.h>

#include "Graphic/CAnchor.h"
#include "Data/CDataLoader.h"
#include "Effect/CEffectParent.h"
#include "Effect/CEffect_BulletDelete.h"
#include "Effect/CEffect_DamageNumber.h"
#include "Field/CField.h"
#include "Graphic/Image/CImageManager.h"

CMover_BulletBase::CMover_BulletBase(std::string GID, CStatus baseparams,
                                     CVector position, CVector velocity)
    : CMover(kBullet, position, 0, velocity, 0, COF(), 0),
      base_params_(baseparams),
      atk_(CAttribute(0)),
      color_(0) {
  LoadStatus(GID);
}

void CMover_BulletBase::BaseUpdate() {}

bool CMover_BulletBase::BaseRender() const {
  auto p = CAnchor::GetIns().GetAnchoredPosition(position_);
  if (p.x_ + size_ > 0 && p.x_ - size_ < Constant::kScreenW &&
      p.y_ + size_ > 0 && p.y_ - size_ < Constant::kScreenH)
    return true;
  return false;
}

void CMover_BulletBase::Dead() {
  CEffectParent::RegisterEffect(std::make_shared<CEffect_BulletDelete>(
      position_, velocity_, size_ * 2, color_));
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

void CMover_BulletBase::LoadStatus(std::string GID) {
  auto e = CDataLoader::GetIns().Get("main")->GetChild("bullet")->GetChild(GID);
  mass_ = e->GetChild("mass")->GetInt();
  size_ = ceil(e->GetChild("size")->GetInt() / 2);
  atk_.Load(e->GetChild("atk"));
  cofs_.Load(e->GetChild("cof"));
  color_ = e->GetChild("effc")->GetInt();
}

void CMover_BulletBase::FieldDispatch(CField* f) { f->AttributeEffect(this); }