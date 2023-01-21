#include "CField_Wall_Log.h"

#include <DxLib.h>

CField_Wall_Log::CField_Wall_Log(std::string gid, CVector position, int state)
    : CField_Wall(gid, position, COF().setFrictionCF(0.9)),
      animCount(0.0),
      state(state),
      BurningTime(600) {}

void CField_Wall_Log::Update() {
  switch (state) {
    case 0:
      if (Temperature > 100) state = 1;
      isWall = true;
      break;
    case 1:
      animCount += 0.15;
      animCount = std::fmod(animCount, 3);
      BurningTime--;
      // if (BurningTime < 0)state = 2;
      Damage = CAttribute(0.0).FIRE(6.0);
      isWall = false;
      break;
    case 2:
      Damage = CAttribute(0.0);
      isWall = false;
      break;
  }
}

void CField_Wall_Log::Render() const {
  switch (state) {
    case 1:
      CImageManager::getIns()
          .find("effect_flame")
          ->DrawRotaFwithBlend(Position.x, Position.y, GetRand(16) / 256.0f,
                               1.0, 0xFFFFFF, CImageManager::BM_ADD, 216,
                               Constant::priority_effect, (unsigned int)animCount);
      CImageManager::getIns()
          .find("Field_Grass")
          ->DrawRota(Position, 0.0, 1.0,
                     Constant::priority_decoration, 4);
      break;
    case 0:
      CImageManager::getIns()
          .find("Field_Grass")
          ->DrawRota(Position, 0.0, 1.0, Constant::priority_wall,
                     4);
      break;
    case 2:
      CImageManager::getIns()
          .find("Field_Grass")
          ->DrawRota(Position, 0.0, 1.0, Constant::priority_wall,
                     5);
      break;
  }
}

CField* CField_Wall_Log::Clone(CVector position) {
  return new CField_Wall_Log(GID, position, state);
}
