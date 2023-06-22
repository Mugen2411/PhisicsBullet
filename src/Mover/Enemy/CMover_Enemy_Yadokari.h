#pragma once
#include "CMover_Enemy.h"

class CMover_Enemy_Yadokari : public CMover_EnemyBase {
  CVector test_dest_;
  int cnt_ = 0;
  double focus_;

 public:
  CMover_Enemy_Yadokari(CVector position, int Level);
  int Update();
  void Render() const;

  CMover_EnemyBase* Clone(CVector position, int Level);
};
