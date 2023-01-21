#include "CField_Dirt.h"

#include <DxLib.h>

CField_Dirt::CField_Dirt(std::string gid, CVector position, int state)
    : CField(gid, position, CVector(32.0, 32.0), COF().setFrictionCF(0.9), 0.0),
      state(state) {
  if (state == 1) Cofs.setFrictionCF(0.7);
}

void CField_Dirt::Update() {}

void CField_Dirt::Render() const {
  CImageManager::getIns()
      .find("Field_Grass")
      ->DrawRota(Position, 0.0, 1.0, Constant::priority_field,
                 24 + state);
}

CField* CField_Dirt::Clone(CVector position) {
  return new CField_Dirt(GID, position, state);
}
