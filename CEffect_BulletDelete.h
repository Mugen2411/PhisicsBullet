#pragma once
#include "CEffect.h"
class CEffect_BulletDelete : public CEffect {
  CVector Velocity;
  int cnt = 0;
  double Size;
  int Color;

 public:
  CEffect_BulletDelete(CVector position, CVector velocity, double size,
                       int color);

  void Update();
  void Render() const;
};
