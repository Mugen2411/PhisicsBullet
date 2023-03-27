#include "CImageManager.h"
#include "CMover_Shot_Archer_ThunderArrow.h"

CMover_Shot_Archer_ThunderArrow::CMover_Shot_Archer_ThunderArrow(CAttribute baseATK,
                                                             CVector position,
                                                             double angle)
    : CMover_ShotBase("S_Archer_ThunderArrow", baseATK, position,
                      CVector(angle) * 48.0) {}

int CMover_Shot_Archer_ThunderArrow::Update() {
  if (velocity_.GetLength() < Constant::kDynamicBorder)
    SetStatus(Status::kDead);
  return status_;
}

void CMover_Shot_Archer_ThunderArrow::Render() const {
  CEffect_Bright::GetIns().Register(
      CEffect_Bright::BrightDesc(position_, 96.0, 128));
  CImageManager::GetIns()
      .Find("shot_archer_arrow")
      ->DrawRota(position_, velocity_.GetAngle(), 1.0, Constant::kPriorityShot,
                 3);
}
