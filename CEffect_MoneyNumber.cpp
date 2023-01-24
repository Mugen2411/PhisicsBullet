#include "CEffect_MoneyNumber.h"

#include <cmath>

#include "CImageManager.h"

CEffect_MoneyNumber::CEffect_MoneyNumber(CVector position_, int num)
    : CEffect(position_), num_(num), dy_(5.0), cnt_(0) {}

void CEffect_MoneyNumber::Update() {
  position_.y_ -= dy_;
  dy_ *= 0.90;
  cnt_++;
  if (cnt_ > 60) status_ = 1;
}

void CEffect_MoneyNumber::Render() const {
  int l = (int)std::log10(num_) + 1;
  int n = num_;
  int x = (int)position_.x_ + l * 5;
  for (int i = 0; i < l; i++) {
    CImageManager::GetIns()
        .Find("effect_number3")
        ->DrawRota(x, (int)position_.y_, 0.0, 1.0, Constant::kPriorityNumber, n % 10);
    x -= 10;
    n /= 10;
  }
  CImageManager::GetIns()
      .Find("effect_number3")
      ->DrawRota(x, (int)position_.y_, 0.0, 1.0, Constant::kPriorityNumber, 10);
}
