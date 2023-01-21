#pragma once
#include "CEffect.h"

class CEffect_Wind : public CEffect {
  CVector basePos;
  int cnt = 0;
  int duration;
  float power, angle, width, length;
  float delta;
  float x, y, z;

 public:
  CEffect_Wind(CVector position, float power, float angle, float width,
               float length);

  void Update();
  void Render() const;
};
