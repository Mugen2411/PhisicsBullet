#include "CMover_Shot_Archer_PlaneArrow.h"

#include "CImageManager.h"

CMover_Shot_Archer_PlaneArrow::CMover_Shot_Archer_PlaneArrow(CAttribute baseATK,
                                                             CVector position,
                                                             double angle)
    : CMover_ShotBase(baseATK, CAttribute(0.0).None(40), position, 24,
                      CVector(angle) * 24.0, 0.2, COF(0.0, 0.5, 0.15, 0.0),
                      0x7F7F7F) {}

int CMover_Shot_Archer_PlaneArrow::Update() {
  if (velocity_.GetLength2() < Constant::kZeroBorder) SetStatus(Status::kDead);
  return status_;
}

void CMover_Shot_Archer_PlaneArrow::Render() const {
  CImageManager::GetIns()
      .Find("shot_archer_arrow")
      ->DrawRota(position_, velocity_.GetAngle(), 1.0,
                  Constant::kPriorityShot, 0);
}
