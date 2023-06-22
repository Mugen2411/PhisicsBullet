#include "CEffect_DamageNumber.h"

#include <DxLib.h>

CEffect_DamageNumber::CEffect_DamageNumber(CVector position_, double num,
                                           int type, int Style)
    : CEffect(position_),
      num_(num),
      type_(type),
      cnt_(0),
      style_(Style),
      dy_(4.0),
      number_drawer_() {}

void CEffect_DamageNumber::Update() {
  cnt_++;
  position_.y_ -= dy_;
  dy_ *= 0.83;
  if (cnt_ > 30) status_ = 1;
}

void CEffect_DamageNumber::Render() const {
  number_drawer_.Draw(
      (int)position_.x_, (int)position_.y_, num_, type_, style_,
      style_ == 0 ? Constant::kPriorityNumber + 1 : Constant::kPriorityNumber);
}
