#include "CField_Wall_DeepWater.h"

CField_Wall_DeepWater::CField_Wall_DeepWater(std::string gid, CVector position_)
    : CField_Wall(gid, position_, COF()) {}

void CField_Wall_DeepWater::Update() {}

void CField_Wall_DeepWater::Render() const {
  CImageManager::GetIns()
      .Find("Field_IceFloor")
      ->DrawRota(position_, 0, 1, Constant::kPriorityWall, 2);
}

CField* CField_Wall_DeepWater::Clone(CVector position_) {
  return new CField_Wall_DeepWater(gid_, position_);
}
