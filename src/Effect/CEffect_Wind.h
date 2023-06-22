#pragma once
#include "CEffect.h"

class CEffect_Wind : public CEffect {
 public:
  CEffect_Wind(CVector position_, double power, float angle, double width,
               double length);

  void Update();
  void Render() const;

 private:
  CVector base_position_;
  int cnt_ = 0;
  int duration_;
  double power_, width_, length_;
  float delta_, angle_;
  float x_, y_, z_;
};
