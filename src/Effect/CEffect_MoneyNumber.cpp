#include "CEffect_MoneyNumber.h"

#include <cmath>

#include "Graphic/Image/CImageManager.h"

CEffect_MoneyNumber::CEffect_MoneyNumber(CVector position_, double num)
    : CEffect(position_), num_(num), dy_(5.0), cnt_(0), cnd_() {}

void CEffect_MoneyNumber::Update() {
  position_.y_ -= dy_;
  dy_ *= 0.90;
  cnt_++;
  if (cnt_ > 40) status_ = 1;
}

void CEffect_MoneyNumber::Render() const {
  cnd_.Draw((int)position_.x_, (int)position_.y_, num_, 0, 2, Constant::kPriorityNumber);
}
