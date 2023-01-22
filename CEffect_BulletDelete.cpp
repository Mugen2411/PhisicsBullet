#include "CEffect_BulletDelete.h"

#include "CImageManager.h"

CEffect_BulletDelete::CEffect_BulletDelete(CVector position_, CVector velocity,
                                           double size, int color)
    : CEffect(position_),
      velocity_(velocity * 0.5),
      size_(size),
      color_(color),
      cnt_(0) {}

void CEffect_BulletDelete::Update() {
  position_ += velocity_;
  cnt_++;
  if (cnt_ / 2.0 > 7) status_ = 1;
}

void CEffect_BulletDelete::Render() const {
  CImageManager::GetIns()
      .Find("effect_bulletdelete")
      ->DrawRotaFwithBlend(position_.x, position_.y, velocity_.GetAngle(),
                           float(size_) / 16.0f, color_, CImageManager::kNone,
                           255, Constant::kPriorityEffect,
                           (uint32_t)(cnt_ / 2.0));
  CImageManager::GetIns()
      .Find("effect_bulletdelete")
      ->DrawRotaFwithBlend(position_.x, position_.y, velocity_.GetAngle(),
                           float(size_) / 16.0f, 0xFFFFFF, CImageManager::kAdd,
                           255, Constant::kPriorityEffect + 1,
                           (uint32_t)(cnt_ / 2.0));
}
