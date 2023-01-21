#pragma once
#include "CMediator.h"

class CParts {
  CMediator* med;

 public:
  CParts(CMediator* m) : med(m){};
  virtual ~CParts() {}
  virtual void Changed() { med->PartsChanged(this); }
};
