#include "CField_Lava.h"

#include <DxLib.h>

#include "CEffect_Bright.h"

CField_Lava::CField_Lava(std::string gid, CVector position_, double temperature)
    : CField(gid, position_, CVector(32.0, 32.0), COF().SetFrictionCF(0.6),
             temperature, CAttribute(0.0)) {}

void CField_Lava::Update() {
  if (temperature_ < 0) {
    cofs_.SetWaterResCF(0.0).SetFrictionCF(0.6);
    damage_ = CAttribute(0.0);
  } else {
    cofs_.SetWaterResCF(0.9).SetFrictionCF(0.1);
    damage_ = CAttribute(0.0).None(0.0).Fire(15.0);
  }
}

void CField_Lava::Render() const {
  if (temperature_ < 0)
    CImageManager::GetIns()
        .Find("Field_Lava")
        ->DrawRota(position_, 0.0, 1.0, Constant::kPriorityField,
                   1);
  else {
    CEffect_Bright::GetIns().Register(
        CEffect_Bright::BrightDesc(position_, 512 - GetRand(16), 64));
    CImageManager::GetIns()
        .Find("Field_Lava")
        ->DrawRota(position_, 0.0, 1.0, Constant::kPriorityField,
                   0);
  }
}

CField* CField_Lava::Clone(CVector position_) {
  return new CField_Lava(gid_, position_, temperature_);
}
