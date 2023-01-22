#pragma once
#include "CMover.h"
#include "CPowerParent.h"

class CPower {
 public:
  CPower(CVector position, double power, int duration);
  void SetParent(CPowerParent* p) { parent_ = p; }

  virtual void ApplyForceToMover(CMover*) = 0;
  virtual int Update() = 0;
  virtual void Render() const = 0;

 protected:
  CPowerParent* parent_;
  CVector position_;
  double power_;
  int duration_;
  int cnt_;
};
