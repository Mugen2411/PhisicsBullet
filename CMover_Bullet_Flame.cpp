#include "CMover_Bullet_Flame.h"

CMover_Bullet_Flame::CMover_Bullet_Flame(CStatus baseparams, CVector position,
                                         double angle, double speed)
    : CMover_BulletBase(baseparams, CAttribute(0.0).None(2).Fire(18), position,
                        16, CVector(angle) * speed, 0.5,
                        COF(0.005, 0.005, 0.04, 0.1), 0xFF0000),
      base_angle_(0.0),
      animation_cnt_(0.0) {}

int CMover_Bullet_Flame::Update() {
  animation_cnt_ += 0.24;
  if (animation_cnt_ > 4.0) animation_cnt_ = 0.0;
  base_angle_ += (float)(Constant::kPI2 * 3 * Constant::kPerFrame);
  if (velocity_.GetLength2() < Constant::kBulletDeleteVelocity)
    SetStatus(Status::kDead);
  return status_;
}

void CMover_Bullet_Flame::Render() const {
  CImageManager::GetIns()
      .Find("effect_flame")
      ->DrawRotaFwithBlend(position_.x_, position_.y_,
                           velocity_.GetAngle() + base_angle_, 1.0, 0xFFFFFF,
                           CImageManager::BlendMode::kAdd, 0xFF,
                           Constant::kPriorityBullet, (uint32_t)animation_cnt_);
}