#pragma once
#include "CMediator.h"

class CParts {
 public:
  CParts(CMediator* m) : med_(m){};
  virtual ~CParts() {}
  virtual void Changed() { med_->PartsChanged(this); }

 private:
  CMediator* med_;
};
