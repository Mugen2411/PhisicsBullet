#include "CEffect_Wind.h"

#include <DxLib.h>

#include "Graphic/Image/CImageManager.h"

CEffect_Wind::CEffect_Wind(CVector position_, double power, float angle,
                           double width, double length)
    : CEffect(position_),
      base_position_(position_),
      duration_((int)std::abs(length / power)),
      power_(power),
      width_(width),
      length_(length),
      delta_(GetRand(100) * 0.01f * (float)Constant::kPI2),
      angle_(angle),
      x_(0),
      y_(0),
      z_(0) {}

void CEffect_Wind::Update() {
  if (cnt_ > duration_) {
    status_ = 1;
    return;
  }
  z_ = (float)(Constant::kPI2 * Constant::kPerFrame * (duration_ / 4) * cnt_);
  x_ = cosf(z_ + delta_) * (float)width_ * 0.5f;
  y_ = cnt_ * (float)power_;
  z_ = (sinf(z_ + delta_) + 1.0f) * 0.5f;
  position_.x_ = cos(angle_) * y_ + cos(angle_ + Constant::kPI / 2) * x_;
  position_.y_ = sin(angle_) * y_ + sin(angle_ + Constant::kPI / 2) * x_;
  position_ += base_position_;
  cnt_++;
}

void CEffect_Wind::Render() const {
  CImageManager::GetIns()
      .Find("effect_wind")
      ->DrawRotaFwithBlend(
          position_.x_, position_.y_, angle_,
          power_ > 0
              ? ((float)(duration_ - cnt_) / duration_ * 0.5f + 0.5f) / 4.0f
              : ((float)(cnt_) / duration_ * 0.5f + 0.5f) / 4.0f,
          0xFFFFFF,
          CImageManager::BlendMode::kAlpha, int(z_ * 0xFF),
          Constant::kPriorityEffect, 1);
}
