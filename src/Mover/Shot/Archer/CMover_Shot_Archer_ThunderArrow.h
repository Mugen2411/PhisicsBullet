#pragma once
#include "Effect/CEffect_Bright.h"
#include "Mover/Shot/CMover_ShotBase.h"

class CMover_Shot_Archer_ThunderArrow : public CMover_ShotBase {
 public:
  CMover_Shot_Archer_ThunderArrow(CAttribute baseATK, CVector position,
                                double angle);
  int Update();
  void Render() const;
};
