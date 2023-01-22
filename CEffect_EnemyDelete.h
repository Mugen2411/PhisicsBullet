#pragma once
#include "CEffect.h"
class CEffect_EnemyDelete : public CEffect {
 public:
  CEffect_EnemyDelete(CVector position_, double size, int color, int duration);

  void Update();
  void Render() const;

 private:
  int cnt_ = 0;
  double size_;
  int color_;
  double animation_cnt_;
  int duration_;
};
