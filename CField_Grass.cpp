#include "CField_Grass.h"

#include <DxLib.h>

#include "CEffect_Bright.h"

CField_Grass::CField_Grass(std::string gid, CVector position)
    : CField(gid, position, CVector(32.0, 32.0), COF().setFrictionCF(0.7), 0),
      animCount(0),
      BurningTime(0),
      state(0),
      Fertile(0) {
  if (GetRand(3) != 0)
    decoration = 0;
  else {
    if (GetRand(1) == 0)
      decoration = 1;
    else
      decoration = 2;
  }
}

void CField_Grass::Update() {
  switch (state) {
    case 0:
      if (Temperature > 100.0) {
        state = 1;
        BurningTime = 600;
      }
      break;
    case 1:
      Damage.FIRE(8.0);
      animCount += 0.15;
      animCount = std::fmod(animCount, 3);
      BurningTime--;
      if (BurningTime < 0 || Temperature < 0) {
        state = 2;
      }
      break;
    case 2:
      Damage = CAttribute(0.0);
      if (Fertile > 200.0) {
        state = 0;
        Temperature = 0;
      }
      break;
  }
}

void CField_Grass::Render() const {
  if (state == 0)
    CImageManager::getIns()
        .find("Field_Grass")
        ->DrawRota(Position.x, Position.y, 0.0, 1.0, Constant::priority_field,
                   decoration);
  else
    CImageManager::getIns()
        .find("Field_Grass")
        ->DrawRota(Position.x, Position.y, 0.0, 1.0, Constant::priority_field,
                   28);

  if (state == 1) {
    CEffect_Bright::getIns().Register(
        CEffect_Bright::BrightDesc(Position, 128 - GetRand(16), 216));
    CImageManager::getIns()
        .find("effect_flame")
        ->DrawRotaFwithBlend(Position.x, Position.y, GetRand(16) / 256.0f, 1.0,
                             0xFFFFFF, CImageManager::BM_ADD, 216,
                             Constant::priority_effect, animCount);
  }
}

CField* CField_Grass::Clone(CVector position) {
  return new CField_Grass(GID, position);
}
