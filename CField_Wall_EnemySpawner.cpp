#include "CField_Wall_EnemySpawner.h"

CField_Wall_EnemySpawner::CField_Wall_EnemySpawner(std::string gid,
                                                   CVector position, int index)
    : CField(gid, position, CVector(32, 32), COF(0, 0, 0, 0), 0),
      index(index),
      CND() {}

void CField_Wall_EnemySpawner::Update() {}

void CField_Wall_EnemySpawner::Render() const {
  CND.Draw(Position.x, Position.y, index, 0, 0, 7);
}

CField* CField_Wall_EnemySpawner::Clone(CVector position) {
  return new CField_Wall_EnemySpawner(GID, position, index);
}
