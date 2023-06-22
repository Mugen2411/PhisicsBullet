#pragma once
#include "CMover_BulletBase.h"
class CMover_Bullet_CornFrost : public CMover_BulletBase {
 public:
  CMover_Bullet_CornFrost(CStatus baseparams, CVector position, double angle,
                     double speed);
  int Update();
  void Render() const;
};
