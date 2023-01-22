#pragma once
#include "CMover_BulletBase.h"
class CMover_Bullet_Axe : public CMover_BulletBase {
 public:
  CMover_Bullet_Axe(CStatus baseparams, CVector position, double angle,
                    double speed);
  int Update();
  void Render() const;

 protected:
  float base_angle_;
};
