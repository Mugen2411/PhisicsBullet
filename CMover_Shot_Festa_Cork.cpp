#include "CMover_Shot_Festa_Cork.h"

#include "CImageManager.h"

CMover_Shot_Festa_Cork::CMover_Shot_Festa_Cork(CAttribute baseATK,
                                               CVector position, double angle)
    : CMover_ShotBase(baseATK, CAttribute(0.0).None(30), position, 16,
                      CVector(angle) * 16.0, 0.1, COF(0.001, 0.4, 0.1, 0.7),
                      0xFF7F00) {}

int CMover_Shot_Festa_Cork::Update() {
  if (velocity_.GetLength2() < Constant::kZeroBorder) SetStatus(Status::kDead);
  return status_;
}

void CMover_Shot_Festa_Cork::Render() const {
  CImageManager::GetIns()
      .Find("shot_festa_cork")
      ->DrawRota(position_, velocity_.GetAngle(), 1.0,
                  Constant::kPriorityShot);
}
