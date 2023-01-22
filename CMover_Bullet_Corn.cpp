#include "CMover_Bullet_Corn.h"

CMover_Bullet_Corn::CMover_Bullet_Corn(CStatus baseparams, CVector position,
                                       double angle, double speed)
    : CMover_BulletBase(baseparams, CAttribute(0.0).None(50).Flower(50),
                        position, 16, CVector(angle) * speed, 1,
                        COF(0.005, 0.2, 0.03, 0.1), 0xFFFF00) {}

int CMover_Bullet_Corn::Update() {
  if (velocity_.GetLength2() < Constant::kBulletDeleteVelocity)
    SetStatus(Status::kDead);
  return status_;
}

void CMover_Bullet_Corn::Render() const {
  CImageManager::GetIns()
      .Find("bullet_corn")
      ->DrawRota(position_, velocity_.GetAngle(), 1.0,
                 Constant::kPriorityBullet);
}