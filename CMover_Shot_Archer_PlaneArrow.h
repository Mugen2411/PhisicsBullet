#pragma once
#include "CMover_ShotBase.h"

class CMover_Shot_Archer_PlaneArrow : public CMover_ShotBase {
 public:
  CMover_Shot_Archer_PlaneArrow(CAttribute baseATK, CVector position,
                                double angle);
  int Update();
  void Render() const;
};
