#include "CEffect_CoinDelete.h"

#include "CEffect_Bright.h"
#include "CImageManager.h"

CEffect_CoinDelete::CEffect_CoinDelete(CVector position_, double size, int type)
    : CEffect(position_),
      size_(size),
      cnt_(0.0f),
      type_(type),
      color_{0x003F4F, 0,        0,        0xDF00FF, 0xDF00FF,
             0x0000FF, 0x0000FF, 0x00FFFF, 0x00FFFF, 0x00FF00,
             0x00FF00, 0xFFFF00, 0xFFFF00, 0xFF7F00, 0xFF7F00,
             0xFF0000, 0xFF0000, 0xCFCFCF, 0xCFCFCF, 0xCFAF00,
             0xCFAF00, 0x007FCF, 0x007FCF, 0x7F2F00, 0x7F2F00} {}

void CEffect_CoinDelete::Update() {
  color_[1] = HSV2RGB(cnt_ / 4.0f, 1.0, 0.75);
  color_[2] = HSV2RGB(cnt_ / 4.0f, 1.0, 0.75);
  cnt_ += 0.2f;
  if (cnt_ > 4.0) status_ = 1;
}

void CEffect_CoinDelete::Render() const {
  CImageManager::GetIns()
      .Find("effect_coindelete")
      ->DrawRotaFwithBlend(position_.x_, position_.y_, 0.0, float(size_),
                           color_[type_], CImageManager::BlendMode::kNone, 0xFF,
                           Constant::kPriorityEffect, (uint32_t)(cnt_));
  CImageManager::GetIns()
      .Find("effect_coindelete")
      ->DrawRotaFwithBlend(position_.x_, position_.y_, 0.0, float(size_),
                           0xFFFFFF, CImageManager::BlendMode::kAdd, 0xFF,
                           Constant::kPriorityEffect + 1, (uint32_t)(cnt_) + 4);
  CEffect_Bright::GetIns().Register(
      CEffect_Bright::BrightDesc{position_, size_ * 32.0, 96});
}
