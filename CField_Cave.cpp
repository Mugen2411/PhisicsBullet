#include "CField_Cave.h"

#include <DxLib.h>

CField_Cave::CField_Cave(std::string gid, CVector position)
    : CField(gid, position, CVector(32.0, 32.0), COF().setFrictionCF(0.5), 0),
      animCount(0) {
  if (GetRand(3) != 0)
    decoration = 0;
  else {
    if (GetRand(1) == 0)
      decoration = 1;
    else
      decoration = 2;
  }
}

void CField_Cave::Update() {}

void CField_Cave::Render() const {
  CImageManager::getIns()
      .find("Field_Cave")
      ->DrawRota(Position, 0.0, 1.0, Constant::priority_field,
                 decoration);
}

CField* CField_Cave::Clone(CVector position) {
  return new CField_Cave(GID, position);
}
