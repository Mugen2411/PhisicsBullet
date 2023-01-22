#pragma once
#include "CMover_Enemy.h"

class CMover_Enemy_Bud : public CMover_EnemyBase {
  CVector test_dest_;
  int cnt_ = 0;

 public:
  CMover_Enemy_Bud(CVector position, int Level);
  int Update();
  void Render() const;

  CMover_EnemyBase* Clone(CVector position, int Level);
};
