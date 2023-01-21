#include "CMover_Bullet_Corn.h"

CMover_Bullet_Corn::CMover_Bullet_Corn(CStatus baseparams, CVector position,
                                       double angle, double speed)
    : CMover_BulletBase(baseparams, CAttribute(0.0).NONE(50).FLOWER(50),
                        position, 16, CVector(angle) * speed, 1,
                        COF(0.005, 0.2, 0.03, 0.1), 0xFFFF00) {}

int CMover_Bullet_Corn::Update() {
  if (Velocity.getLength2() < Constant::bullet_delete_velocity)
    setStatus(STATUS::DEAD);
  return Status;
}

void CMover_Bullet_Corn::Render() const {
  CImageManager::getIns()
      .find("bullet_corn")
      ->DrawRota(Position.x, Position.y, Velocity.getAngle(), 1.0,
                 Constant::priority_bullet);
}