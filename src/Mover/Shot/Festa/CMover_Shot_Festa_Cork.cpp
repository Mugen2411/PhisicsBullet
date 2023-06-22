#include "CMover_Shot_Festa_Cork.h"

#include "Graphic/Image/CImageManager.h"

CMover_Shot_Festa_Cork::CMover_Shot_Festa_Cork(CAttribute baseATK,
                                               CVector position, double angle)
    : CMover_ShotBase("S_Festa_Cork", baseATK, position, CVector(angle) * 16.0) {}

int CMover_Shot_Festa_Cork::Update() {
  if (velocity_.GetLength() < Constant::kDynamicBorder) SetStatus(Status::kDead);
  return status_;
}

void CMover_Shot_Festa_Cork::Render() const {
  CImageManager::GetIns()
      .Find("shot_festa_cork")
      ->DrawRota(position_, velocity_.GetAngle(), 1.0,
                  Constant::kPriorityShot);
}
