#include "CField_Dirt.h"

#include <DxLib.h>

CField_Dirt::CField_Dirt(std::string gid, CVector position_, int state_)
    : CField(gid, position_, CVector(32.0, 32.0), COF().SetFrictionCF(0.9), 0.0),
      state_(state_) {
  if (state_ == 1) cofs_.SetFrictionCF(0.7);
}

void CField_Dirt::Update() {}

void CField_Dirt::Render() const {
  CImageManager::GetIns()
      .Find("Field_Grass")
      ->DrawRota(position_, 0.0, 1.0, Constant::kPriorityField,
                 24 + state_);
}

CField* CField_Dirt::Clone(CVector position_) {
  return new CField_Dirt(gid_, position_, state_);
}
