#include "CMover_Bullet_Ice.h"

CMover_Bullet_Ice::CMover_Bullet_Ice(CStatus baseparams, CVector position,
                                       double angle, double speed)
    : CMover_BulletBase("B_Ice", baseparams, position,
                        CVector(angle) * speed) {}

int CMover_Bullet_Ice::Update() {
  if (velocity_.GetLength() < Constant::kDynamicBorder)
    SetStatus(Status::kDead);
  return status_;
}

void CMover_Bullet_Ice::Render() const {
  CImageManager::GetIns()
      .Find("bullet_ice")
      ->DrawRota(position_, velocity_.GetAngle(), 1.0,
                 Constant::kPriorityBullet);
}