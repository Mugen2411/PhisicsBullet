#pragma once
#include "Mover/Shot/CMover_ShotBase.h"

class CMover_Shot_Burner_Flame : public CMover_ShotBase {
 public:
  CMover_Shot_Burner_Flame(CAttribute baseATK, CVector position,
                               double angle);

  int Update();
  void Render() const;

 private:
  const int kEffectiveDuration_;

  int cnt_;
  float base_angle_;
  double animation_cnt_;
};
