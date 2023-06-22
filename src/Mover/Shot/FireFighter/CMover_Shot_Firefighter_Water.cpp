#include "CMover_Shot_Firefighter_Water.h"

#include "Graphic/Image/CImageManager.h"

CMover_Shot_Firefigher_Water::CMover_Shot_Firefigher_Water(CAttribute baseATK,
                                                           CVector position,
                                                           double angle)
    : CMover_ShotBase("S_Firefighter_Water", baseATK, position,
                      CVector(angle) * 12.0),
      cnt_(0),
      kEffectiveDuration_(16) {}

int CMover_Shot_Firefigher_Water::Update() {
  if (velocity_.GetLength() < Constant::kDynamicBorder) {
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
      ->DrawRotaF(position_, velocity_.GetAngle(), 1,
                  Constant::kPriorityShot);
}
