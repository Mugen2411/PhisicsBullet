#include "CField_IceFloor.h"

#include <DxLib.h>

CField_IceFloor::CField_IceFloor(std::string gid, CVector position_,
                                 double temperature)
    : CField(gid, position_, CVector(32.0, 32.0), COF().SetFrictionCF(0.5),
             temperature, CAttribute(0.0).Ice(2.0)) {}

void CField_IceFloor::Update() {
  if (temperature_ < 0) {
    cofs_.SetWaterResCF(0.0).SetFrictionCF(0.1);
    damage_ = CAttribute(0.0).Ice(4.0);
  } else {
    cofs_.SetWaterResCF(0.8).SetFrictionCF(0.2);
    damage_ = CAttribute(0.0).Aqua(4.0);
  }
}

void CField_IceFloor::Render() const {
  if (temperature_ < 0)
    CImageManager::GetIns()
        .Find("Field_IceFloor")
        ->DrawRota(position_, 0.0, 1.0, Constant::kPriorityField,
                   0);
  else
    CImageManager::GetIns()
        .Find("Field_IceFloor")
        ->DrawRota(position_, 0.0, 1.0, Constant::kPriorityField,
                   1);
}

CField* CField_IceFloor::Clone(CVector position_) {
  return new CField_IceFloor(gid_, position_, temperature_);
}
