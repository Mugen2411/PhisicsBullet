#pragma once
#include "CEffect.h"
class CEffect_Bat_Swing : public CEffect {
 public:
  CEffect_Bat_Swing(CVector position_, float angle);

  void Update();
  void Render() const;

 private:
  float angle_;
  int cnt_ = 0;
  int color_;
};
