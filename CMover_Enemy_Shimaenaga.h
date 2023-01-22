#pragma once
#include "CMover_Enemy.h"
class CMover_Enemy_Shimaenaga : public CMover_EnemyBase {
 protected:
  double animation_cnt_;

 public:
  CMover_Enemy_Shimaenaga(CVector position, int Level);
  int Update();
  void Render() const;

  CMover_EnemyBase* Clone(CVector position, int Level);
};
