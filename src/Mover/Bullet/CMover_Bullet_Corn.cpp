#include "CMover_Bullet_Corn.h"

CMover_Bullet_Corn::CMover_Bullet_Corn(CStatus baseparams, CVector position,
                                       double angle, double speed)
    : CMover_BulletBase("B_Corn", baseparams, position, CVector(angle) * speed) {}

int CMover_Bullet_Corn::Update() {
  if (velocity_.GetLength() < Constant::kDynamicBorder)
    SetStatus(Status::kDead);
  return status_;
}

void CMover_Bullet_Corn::Render() const {
  CImageManager::GetIns()
      .Find("bullet_corn")
      ->DrawRota(position_, velocity_.GetAngle(), 1.0,
                 Constant::kPriorityBullet);
}