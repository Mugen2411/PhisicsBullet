#include "CMover_Shot_Festa_Superball.h"

#include "CImageManager.h"

CMover_Shot_Festa_Superball::CMover_Shot_Festa_Superball(CAttribute baseATK,
                                                         CVector position,
                                                         double angle)
    : CMover_ShotBase(
          baseATK, CAttribute(0.0).None(18), position, 12,
          CVector(angle) * 16.0 * (0.8 + 0.4 * (GetRand(100) * 0.01)), 0.5,
          COF(0.01, 0.09, 0.001, 1.0), 0),
      color_(0) {
  color_ = GetRand(3);
  effect_color_ = effect_color[color_];
}

int CMover_Shot_Festa_Superball::Update() {
  cnt_++;
  if (cnt_ > 300) SetStatus(Status::kDead);
  if (velocity_.GetLength2() < Constant::kZeroBorder) SetStatus(Status::kDead);
  return status_;
}

void CMover_Shot_Festa_Superball::Render() const {
  CImageManager::GetIns()
      .Find("shot_festa_superball")
      ->DrawRota(position_, velocity_.GetAngle(), 1.0,
                  Constant::kPriorityShot, color_);
}
