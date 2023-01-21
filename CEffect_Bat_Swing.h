#pragma once
#include "CEffect.h"
class CEffect_Bat_Swing : public CEffect {
  float angle;
  int cnt = 0;
  int Color;

 public:
  CEffect_Bat_Swing(CVector position, float angle);

  void Update();
  void Render() const;
};
