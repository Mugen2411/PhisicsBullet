#pragma once
#include "CPower.h"
class CPower_Line : public CPower {
 public:
  CPower_Line(CVector position, CVector direction, double width, double power,
              int duration);
  bool isHit(CVector mPosition, double size);
  void ApplyForceToMover(CMover*);
  int Update();
  void Render() const;

 protected:
  CVector direction_;       //角度・長さ
  double width_;            //幅
  CVector corner_[4];       //四隅
  CVector force_direction_;  //力をかける方向
};
