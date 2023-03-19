#include "CField_Wall_IceRock.h"

CField_Wall_IceRock::CField_Wall_IceRock(std::string gid, CVector position_)
    : CField_Wall(gid, position_, COF().SetReflectCF(0.6)) {}

void CField_Wall_IceRock::Update() {}

void CField_Wall_IceRock::Render() const {
  CImageManager::GetIns()
      .Find("Field_IceFloor")
      ->DrawRota(position_, 0, 1, Constant::kPriorityWall, 8);
}

CField* CField_Wall_IceRock::Clone(CVector position_) {
  return new CField_Wall_IceRock(gid_, position_);
}
