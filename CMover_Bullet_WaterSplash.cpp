#include "CMover_Bullet_WaterSplash.h"

CMover_Bullet_WaterSplash::CMover_Bullet_WaterSplash(CStatus baseparams,
                                                     CVector position,
                                                     double angle, double speed)
    : CMover_BulletBase(baseparams, CAttribute(0.0).None(20).Aqua(80), position,
                        16, CVector(angle) * speed, 4,
                        COF(0.05, 0.02, 0.002, 0.1), 0x00FFFF) {}

int CMover_Bullet_WaterSplash::Update() {
  if (velocity_.GetLength2() < Constant::kBulletDeleteVelocity)
    SetStatus(Status::kDead);
  return status_;
}

void CMover_Bullet_WaterSplash::Render() const {
  CImageManager::GetIns()
      .Find("bullet_watersplash")
      ->DrawRota(position_, velocity_.GetAngle(), 1.0,
                 Constant::kPriorityBullet);
}