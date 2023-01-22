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
  CVector direction_;       //Šp“xE’·‚³
  double width_;            //•
  CVector corner_[4];       //l‹÷
  CVector force_direction_;  //—Í‚ğ‚©‚¯‚é•ûŒü
};
