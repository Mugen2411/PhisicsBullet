#include "CMover_Bullet_CornFrost.h"

CMover_Bullet_CornFrost::CMover_Bullet_CornFrost(CStatus baseparams, CVector position,
                                       double angle, double speed)
    : CMover_BulletBase("B_CornFrost", baseparams, position,
                        CVector(angle) * speed) {}

int CMover_Bullet_CornFrost::Update() {
  if (velocity_.GetLength() < Constant::kDynamicBorder)
    SetStatus(Status::kDead);
  return status_;
}

void CMover_Bullet_CornFrost::Render() const {
  CImageManager::GetIns()
      .Find("bullet_cornfrost")
      ->DrawRota(position_, velocity_.GetAngle(), 1.0,
                 Constant::kPriorityBullet);
}