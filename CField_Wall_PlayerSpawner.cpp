#include "CField_Wall_PlayerSpawner.h"

#include "CImageManager.h"

CField_Wall_PlayerSpawner::CField_Wall_PlayerSpawner(std::string gid,
                                                     CVector position)
    : CField(gid, position, CVector(32, 32), COF(0, 0, 0, 0), 0) {}

void CField_Wall_PlayerSpawner::Update() {}

void CField_Wall_PlayerSpawner::Render() const {
  CImageManager::getIns()
      .find("player_komuk")
      ->DrawRota(Position.x, Position.y, 0, 1, Constant::priority_enemy, 4);
}

CField* CField_Wall_PlayerSpawner::Clone(CVector position) {
  return new CField_Wall_PlayerSpawner(GID, position);
}