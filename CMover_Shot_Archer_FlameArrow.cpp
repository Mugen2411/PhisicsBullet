#include "CMover_Shot_Archer_FlameArrow.h"

#include "CImageManager.h"

CMover_Shot_Archer_FlameArrow::CMover_Shot_Archer_FlameArrow(CAttribute baseATK,
                                                             CVector position,
                                                             double angle)
    : CMover_ShotBase(baseATK, CAttribute(0.0).None(30).Fire(30), position, 18,
                      CVector(angle) * 32.0, 0.2, COF(0.0, 0.5, 0.15, 0.0),
                      0xFF0000) {}

int CMover_Shot_Archer_FlameArrow::Update() {
  if (velocity_.GetLength2() < Constant::kZeroBorder) SetStatus(Status::kDead);
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
