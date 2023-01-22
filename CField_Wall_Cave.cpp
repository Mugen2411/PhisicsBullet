#include "CField_Wall_Cave.h"

#include "CImageManager.h"

CField_Wall_Cave::CField_Wall_Cave(std::string gid, CVector position_, int state_)
    : CField_Wall(gid, position_, COF().SetReflectCF(0.9)), state_(state_) {
  damage_ = CAttribute(12.0);
}

void CField_Wall_Cave::Update() {}

void CField_Wall_Cave::Render() const {
  CImageManager::GetIns()
      .Find("Field_Cave")
      ->DrawRota(position_, 0.0, 1.0, Constant::kPriorityWall,
                 8 + state_);
}

CField* CField_Wall_Cave::Clone(CVector position_) {
  return new CField_Wall_Cave(gid_, position_, state_);
}
