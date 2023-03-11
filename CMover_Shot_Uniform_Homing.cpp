#include "CMover_Shot_Uniform_Homing.h"

#include "CEffect_Bright.h"
#include "CImageManager.h"

CMover_Shot_Uniform_Homing::CMover_Shot_Uniform_Homing(CAttribute baseATK,
                                                       CVector position,
                                                       double angle)
    : CMover_ShotBase("S_Uniform_Homing", baseATK, position, CVector(angle) * 3.0),
      cnt(0),
      pow(0.0) {}

int CMover_Shot_Uniform_Homing::Update() {
  cnt++;
  if (cnt > 240) {
    status_ = 1;
    return status_;
  }

  pow += 0.5 * Constant::kPerFrame;
  base_atk_ *= 0.992;
  CVector v = GetHomingAngle() * 6.0 - velocity_;
  if (GetHomingAngle().GetLength2() > Constant::kZeroBorder)
    ApplyForce(v.GetNorm() * pow);
  return status_;
}

void CMover_Shot_Uniform_Homing::Render() const {
  CEffect_Bright::GetIns().Register(
      CEffect_Bright::BrightDesc(position_, 48, 128));
  CImageManager::GetIns()
      .Find("shot_uniform_homing")
      ->DrawRota(position_, velocity_.GetAngle(), 1.0, Constant::kPriorityShot);
}
