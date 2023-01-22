#include "CField_Wall_EnemySpawner.h"

CField_Wall_EnemySpawner::CField_Wall_EnemySpawner(std::string gid,
                                                   CVector position_, int index)
    : CField(gid, position_, CVector(32, 32), COF(0, 0, 0, 0), 0),
      index_(index),
      number_drawer_() {}

void CField_Wall_EnemySpawner::Update() {}

void CField_Wall_EnemySpawner::Render() const {
  number_drawer_.Draw((int)position_.x, (int)position_.y, index_, 0, 0, 7);
}

CField* CField_Wall_EnemySpawner::Clone(CVector position_) {
  return new CField_Wall_EnemySpawner(gid_, position_, index_);
}
