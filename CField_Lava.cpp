#include "CField_Lava.h"

#include <DxLib.h>

#include "CEffect_Bright.h"

CField_Lava::CField_Lava(std::string gid, CVector position, double temperature)
    : CField(gid, position, CVector(32.0, 32.0), COF().setFrictionCF(0.6),
             temperature, CAttribute(0.0)) {}

void CField_Lava::Update() {
  if (Temperature < 0) {
    Cofs.setWaterResCF(0.0).setFrictionCF(0.6);
    Damage = CAttribute(0.0);
  } else {
    Cofs.setWaterResCF(0.9).setFrictionCF(0.1);
    Damage = CAttribute(0.0).NONE(0.0).FIRE(15.0);
  }
}

void CField_Lava::Render() const {
  if (Temperature < 0)
    CImageManager::getIns()
        .find("Field_Lava")
        ->DrawRota(Position, 0.0, 1.0, Constant::priority_field,
                   1);
  else {
    CEffect_Bright::getIns().Register(
        CEffect_Bright::BrightDesc(Position, 512 - GetRand(16), 64));
    CImageManager::getIns()
        .find("Field_Lava")
        ->DrawRota(Position, 0.0, 1.0, Constant::priority_field,
                   0);
  }
}

CField* CField_Lava::Clone(CVector position) {
  return new CField_Lava(GID, position, Temperature);
}
