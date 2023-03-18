#include "CField_Wall_PlayerSpawner.h"

#include "CImageManager.h"

CField_Wall_PlayerSpawner::CField_Wall_PlayerSpawner(std::string gid,
                                                     CVector position_)
    : CField(gid, position_, CVector(32, 32), COF(), 0) {}

void CField_Wall_PlayerSpawner::Update() {}

void CField_Wall_PlayerSpawner::Render() const {
  CImageManager::GetIns()
      .Find("player_komuk")
      ->DrawRota(position_, 0, 1, Constant::kPriorityEnemy, 4);
}

CField* CField_Wall_PlayerSpawner::Clone(CVector position_) {
  return new CField_Wall_PlayerSpawner(gid_, position_);
}