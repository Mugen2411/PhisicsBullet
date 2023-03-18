#include "CMover_Shot_Archer_FlameArrow.h"

#include "CImageManager.h"

CMover_Shot_Archer_FlameArrow::CMover_Shot_Archer_FlameArrow(CAttribute baseATK,
                                                             CVector position,
                                                             double angle)
    : CMover_ShotBase("S_Archer_FlameArrow", baseATK, position, CVector(angle) * 48.0) {}

int CMover_Shot_Archer_FlameArrow::Update() {
  if (velocity_.GetLength() < Constant::kDynamicBorder) SetStatus(Status::kDead);
  return status_;
}

void CMover_Shot_Archer_FlameArrow::Render() const {
  CEffect_Bright::GetIns().Register(
      CEffect_Bright::BrightDesc(position_, 96.0, 128));
  CImageManager::GetIns()
      .Find("shot_archer_arrow")
      ->DrawRota(position_, velocity_.GetAngle(), 1.0,
                  Constant::kPriorityShot, 1);
}
