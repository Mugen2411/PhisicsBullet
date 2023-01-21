#pragma once
#include "CEffect_Bright.h"
#include "CMover_ShotBase.h"

class CMover_Shot_Archer_FlameArrow : public CMover_ShotBase {
 public:
  CMover_Shot_Archer_FlameArrow(CAttribute baseATK, CVector position,
                                double angle);
  int Update();
  void Render() const;
};
