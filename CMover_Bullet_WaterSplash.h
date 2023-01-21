#pragma once
#include "CMover_BulletBase.h"
class CMover_Bullet_WaterSplash : public CMover_BulletBase {
 public:
  CMover_Bullet_WaterSplash(CStatus baseparams, CVector position, double angle,
                            double speed);
  int Update();
  void Render() const;
};
