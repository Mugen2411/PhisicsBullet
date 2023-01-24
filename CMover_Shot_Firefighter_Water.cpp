#include "CMover_Shot_Firefighter_Water.h"

#include "CImageManager.h"

CMover_Shot_Firefigher_Water::CMover_Shot_Firefigher_Water(CAttribute baseATK,
                                                           CVector position,
                                                           double angle)
    : CMover_ShotBase(baseATK, CAttribute(0.0).Aqua(20), position, 18,
                      CVector(angle) * 12.0, 2.0, COF(0.0, 0.0, 0.03, 0.0),
                      0x00CFFF),
      cnt_(0),
      kEffectiveDuration_(16) {}

int CMover_Shot_Firefigher_Water::Update() {
  if (velocity_.GetLength2() < Constant::kZeroBorder) {
    SetStatus(kDead);
  }
  cnt_++;
  if (cnt_ > kEffectiveDuration_) {
    base_atk_ *= 0.94;
  }

  return status_;
}

void CMover_Shot_Firefigher_Water::Render() const {
  CImageManager::GetIns()
      .Find("shot_firefighter_water")
      ->DrawRotaF(position_.x_, position_.y_, velocity_.GetAngle(), 1,
                  Constant::kPriorityShot);
}