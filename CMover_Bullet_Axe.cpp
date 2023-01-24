#include "CMover_Bullet_Axe.h"

CMover_Bullet_Axe::CMover_Bullet_Axe(CStatus baseparams, CVector position,
                                     double angle, double speed)
    : CMover_BulletBase(baseparams, CAttribute(0.0).None(100), position, 16,
                        CVector(angle) * speed, 4.0,
                        COF(0.001, 0.05, 0.01, 0.98), 0xFFFFFF),
      base_angle_(0.0) {}

int CMover_Bullet_Axe::Update() {
  base_angle_ += (float)(Constant::kPI2 * Constant::kPerFrame) * 0.8f;
  if (velocity_.GetLength2() < Constant::kBulletDeleteVelocity)
    SetStatus(Status::kDead);
  return status_;
}

void CMover_Bullet_Axe::Render() const {
  CImageManager::GetIns()
      .Find("bullet_axe")
      ->DrawRotaF(position_.x_, position_.y_, velocity_.GetAngle() + base_angle_, 1.0,
                 Constant::kPriorityBullet);
}