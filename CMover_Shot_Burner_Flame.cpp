#include "CImageManager.h"
#include "CMover_Shot_Burner_Flame.h"
#include "CEffect_Bright.h"

CMover_Shot_Burner_Flame::CMover_Shot_Burner_Flame(CAttribute baseATK,
                                                           CVector position,
                                                           double angle)
    : CMover_ShotBase("S_Burner_Flame", baseATK, position,
                      CVector(angle) * 12.0),
      cnt_(0),
      kEffectiveDuration_(16),
      animation_cnt_(0.0),
      base_angle_(0.0f) {}

int CMover_Shot_Burner_Flame::Update() {
  if (velocity_.GetLength() < Constant::kDynamicBorder) {
    SetStatus(kDead);
  }
  cnt_++;
  animation_cnt_ += 0.24;
  if (animation_cnt_ > 4.0) animation_cnt_ = 0.0;
  if (cnt_ > kEffectiveDuration_) {
    base_atk_ *= 0.94;
  }

  return status_;
}

void CMover_Shot_Burner_Flame::Render() const {
  CImageManager::GetIns()
      .Find("effect_flame")
      ->DrawRotaFwithBlend(position_.x_, position_.y_,
                           velocity_.GetAngle() + base_angle_, 1.0f, 0xFFFFFF,
                           CImageManager::BlendMode::kAdd, 0xFF,
                           Constant::kPriorityShot, (uint32_t)animation_cnt_);
  CEffect_Bright::GetIns().Register(
      CEffect_Bright::BrightDesc(position_, 128.0, 48));
}
