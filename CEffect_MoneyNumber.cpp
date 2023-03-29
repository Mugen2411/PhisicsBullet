#include "CEffect_MoneyNumber.h"

#include <cmath>

#include "CImageManager.h"

CEffect_MoneyNumber::CEffect_MoneyNumber(CVector position_, double num)
    : CEffect(position_), num_(num), dy_(5.0), cnt_(0) {}

void CEffect_MoneyNumber::Update() {
  position_.y_ -= dy_;
  dy_ *= 0.90;
  cnt_++;
  if (cnt_ > 60) status_ = 1;
}

void CEffect_MoneyNumber::Render() const {
  int l = (int)std::log10(num_) + 1;
  double n = num_;
  int x = (int)position_.x_ + l * 5;
  for (int i = 0; i < l; i++) {
    CImageManager::GetIns()
        .Find("effect_number3")
        ->DrawRotaFwithBlend(x, (int)position_.y_, 0.0, 1.0, 0xFFFFFF,
                             CImageManager::BlendMode::kAlpha,
                             0xBF - (int)max(0, (10 - cnt_) / 10.0f * 0xBF),
                             Constant::kPriorityNumber, (unsigned int)std::fmodl(n, 10.0));
    x -= 10;
    n /= 10;
  }
  CImageManager::GetIns()
      .Find("effect_number3")
      ->DrawRotaFwithBlend(x, (int)position_.y_, 0.0, 1.0, 0xFFFFFF,
                           CImageManager::BlendMode::kAlpha,
                           0xBF - (int)max(0, (10 - cnt_) / 10.0f * 0xBF),
                           Constant::kPriorityNumber, 10);
}
