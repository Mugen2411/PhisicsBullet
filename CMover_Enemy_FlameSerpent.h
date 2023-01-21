#pragma once
#include "CMover_Enemy.h"

class CMover_Enemy_FlameSerpent : public CMover_EnemyBase {
  CVector testDest;
  int cnt = 0;
  double focus;

 public:
  CMover_Enemy_FlameSerpent(CVector position, int Level);
  int Update();
  void Render() const;

  CMover_EnemyBase* Clone(CVector Position, int Level);
};
