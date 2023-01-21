#include "CField_Wall_Rock.h"

CField_Wall_Rock::CField_Wall_Rock(std::string gid, CVector position)
    : CField_Wall(gid, position, COF().setReflectCF(0.6)) {}

void CField_Wall_Rock::Update() {}

void CField_Wall_Rock::Render() const {
  CImageManager::getIns()
      .find("Field_Cave")
      ->DrawRota(Position.x, Position.y, 0, 1, Constant::priority_wall, 3);
}

CField* CField_Wall_Rock::Clone(CVector position) {
  return new CField_Wall_Rock(GID, position);
}
