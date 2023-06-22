#pragma once
#include "../CMover_ShotBase.h"

class CMover_Shot_Swimsuit_iPhone : public CMover_ShotBase {
 public:
  CMover_Shot_Swimsuit_iPhone(CAttribute baseATK, CVector position,
                              float angle);

  void Dead();

  int Update();
  void Render() const;

 protected:
  float render_angle_;
};
