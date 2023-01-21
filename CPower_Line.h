#pragma once
#include "CPower.h"
class CPower_Line : public CPower {
 protected:
  CVector Direction;       //角度・長さ
  double Width;            //幅
  CVector Corner[4];       //四隅
  CVector ForceDirection;  //力をかける方向

 public:
  CPower_Line(CVector position, CVector direction, double width, double power,
              int duration);
  bool isHit(CVector mPosition, double size);
  void ApplyForceToMover(CMover*);
  int Update();
  void Render() const;
};
