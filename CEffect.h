#pragma once
#include "CVector.h"

class CEffect {
 protected:
  CVector Position;
  int Status;  // 0:�����A1:����
 public:
  CEffect(CVector pos);
  inline bool operator!() { return Status; }
  virtual void Update() = 0;
  virtual void Render() const = 0;
};
