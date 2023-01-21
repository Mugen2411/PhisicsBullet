#pragma once
#include "CEffect.h"

class CEffect_Wind : public CEffect {
  CVector basePos;
  int cnt = 0;
  int duration;
  double power, width, length;
  float delta, angle;
  float x, y, z;

 public:
  CEffect_Wind(CVector position, double power, float angle, double width,
               double length);

  void Update();
  void Render() const;
};
