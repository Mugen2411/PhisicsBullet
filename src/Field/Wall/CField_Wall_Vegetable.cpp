#include "CField_Wall_Vegetable.h"

CField_Wall_Vegetable::CField_Wall_Vegetable(std::string gid, CVector position_,
                                             int col)
    : CField_Wall(gid, position_, COF().SetFrictionCF(0.0)), state_(col) {
  is_wall_ = false;
  damage_ = CAttribute(0.0);
}

void CField_Wall_Vegetable::Update() {}

void CField_Wall_Vegetable::Render() const {
  CImageManager::GetIns()
      .Find("Field_Grass")
      ->DrawRota(position_, 0.0, 1.0,
                 Constant::kPriorityDecoration, 26 + state_);
}

CField* CField_Wall_Vegetable::Clone(CVector position_) {
  return new CField_Wall_Vegetable(gid_, position_, state_);
}
