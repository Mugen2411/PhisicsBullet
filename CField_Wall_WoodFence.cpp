#include "CField_Wall_WoodFence.h"

#include "CImageManager.h"

CField_Wall_WoodFence::CField_Wall_WoodFence(std::string gid, CVector position,
                                             int state)
    : CField_Wall(gid, position, COF().setReflectCF(0.8)), state(state) {
  Damage = CAttribute(12.0);
}

void CField_Wall_WoodFence::Update() {}

void CField_Wall_WoodFence::Render() const {
  CImageManager::getIns()
      .find("Field_Grass")
      ->DrawRota(Position, 0.0, 1.0, Constant::priority_wall,
                 8 + state);
}

CField* CField_Wall_WoodFence::Clone(CVector position) {
  return new CField_Wall_WoodFence(GID, position, state);
}
