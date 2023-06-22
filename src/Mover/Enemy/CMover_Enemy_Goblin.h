#pragma once
#include "CMover_Enemy.h"

class CMover_Enemy_Goblin : public CMover_EnemyBase {
  CVector test_dest_;
  int cnt_ = 0;
  double focus_;

 public:
  CMover_Enemy_Goblin(CVector position, int Level);
  int Update();
  void Render() const;

  CMover_EnemyBase* Clone(CVector position, int Level);
};
