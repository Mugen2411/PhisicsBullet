#pragma once
#include "CMover_Enemy.h"

class CMover_Enemy_Azarashi : public CMover_EnemyBase {
  CVector test_dest_;
  int cnt_ = 0;

 public:
  CMover_Enemy_Azarashi(CVector position, int Level);
  int Update();
  void Render() const;

  CMover_EnemyBase* Clone(CVector position, int Level);
};