#pragma once
#include "CEffect.h"
class CEffect_CoinDelete : public CEffect {
 public:
  CEffect_CoinDelete(CVector position_, double size, int type);

  void Update();
  void Render() const;

 private:
  float cnt_ = 0.0;
  double size_;
  int type_;
  int color_[25];
};
