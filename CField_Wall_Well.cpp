#include "CField_Wall_Well.h"

CField_Wall_Well::CField_Wall_Well(std::string gid, CVector position)
    : CField_Wall(gid, position, COF().setReflectCF(0.9)) {}

void CField_Wall_Well::Update() {}

void CField_Wall_Well::Render() const {
  CImageManager::getIns()
      .find("Field_Grass")
      ->DrawRota(Position.x, Position.y, 0.0, 1.0, Constant::priority_wall, 7);
}

CField* CField_Wall_Well::Clone(CVector position) {
  return new CField_Wall_Well(GID, position);
}
