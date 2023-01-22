#pragma once
#include "CMover_ShotBase.h"

class CMover_Shot_Chinese_Lantern : public CMover_ShotBase {
 public:
  CMover_Shot_Chinese_Lantern(CAttribute baseATK, CVector position,
                              double angle);
  int Update();
  void Render() const;

  void IfOnWall() {}

 private:
  int cnt_;
  CAttribute init_;
  double base_y_;
};
