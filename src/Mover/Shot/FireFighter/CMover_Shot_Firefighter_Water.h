#pragma once
#include "Mover/Shot/CMover_ShotBase.h"

class CMover_Shot_Firefigher_Water : public CMover_ShotBase {
 public:
  CMover_Shot_Firefigher_Water(CAttribute baseATK, CVector position,
                               double angle);

  int Update();
  void Render() const;

 private:
  const int kEffectiveDuration_;

  int cnt_;
};
