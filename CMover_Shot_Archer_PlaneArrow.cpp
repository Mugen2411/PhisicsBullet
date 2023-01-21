#include "CMover_Shot_Archer_PlaneArrow.h"

#include "CImageManager.h"

CMover_Shot_Archer_PlaneArrow::CMover_Shot_Archer_PlaneArrow(CAttribute baseATK,
                                                             CVector position,
                                                             double angle)
    : CMover_ShotBase(baseATK, CAttribute(0.0).NONE(40), position, 24,
                      CVector(angle) * 24.0, 0.2, COF(0.0, 0.5, 0.15, 0.0),
                      0x7F7F7F) {}

int CMover_Shot_Archer_PlaneArrow::Update() {
  if (Velocity.getLength2() < Constant::zero_border) setStatus(STATUS::DEAD);
  return Status;
}

void CMover_Shot_Archer_PlaneArrow::Render() const {
  CImageManager::getIns()
      .find("shot_archer_arrow")
      ->DrawRotaF(Position.x, Position.y, Velocity.getAngle(), 1.0,
                  Constant::priority_shot, 0);
}
