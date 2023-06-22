#include "CField_Wall_Well.h"

CField_Wall_Well::CField_Wall_Well(std::string gid, CVector position_)
    : CField_Wall(gid, position_, COF().SetReflectCF(0.9)) {}

void CField_Wall_Well::Update() {}

void CField_Wall_Well::Render() const {
  CImageManager::GetIns()
      .Find("Field_Grass")
      ->DrawRota(position_, 0.0, 1.0, Constant::kPriorityWall, 7);
}

CField* CField_Wall_Well::Clone(CVector position_) {
  return new CField_Wall_Well(gid_, position_);
}
