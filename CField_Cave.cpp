#include "CField_Cave.h"

#include <DxLib.h>

CField_Cave::CField_Cave(std::string gid, CVector position_)
    : CField(gid, position_, CVector(32.0, 32.0), COF().SetFrictionCF(0.5), 0),
      animation_cnt_(0) {
  if (GetRand(3) != 0)
    decoration_ = 0;
  else {
    if (GetRand(1) == 0)
      decoration_ = 1;
    else
      decoration_ = 2;
  }
}

void CField_Cave::Update() {}

void CField_Cave::Render() const {
  CImageManager::GetIns()
      .Find("Field_Cave")
      ->DrawRota(position_, 0.0, 1.0, Constant::kPriorityField,
                 decoration_);
}

CField* CField_Cave::Clone(CVector position_) {
  return new CField_Cave(gid_, position_);
}