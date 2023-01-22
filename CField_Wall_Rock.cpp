#include "CField_Wall_Rock.h"

CField_Wall_Rock::CField_Wall_Rock(std::string gid, CVector position_)
    : CField_Wall(gid, position_, COF().SetReflectCF(0.6)) {}

void CField_Wall_Rock::Update() {}

void CField_Wall_Rock::Render() const {
  CImageManager::GetIns()
      .Find("Field_Cave")
      ->DrawRota(position_, 0, 1, Constant::kPriorityWall, 3);
}

CField* CField_Wall_Rock::Clone(CVector position_) {
  return new CField_Wall_Rock(gid_, position_);
}
