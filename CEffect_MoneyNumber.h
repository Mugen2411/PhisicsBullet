#pragma once
#include "CEffect.h"
class CEffect_MoneyNumber : public CEffect {
 public:
  CEffect_MoneyNumber(CVector position_, double num);

  void Update();
  void Render() const;

 private:
  double num_;
  double dy_;
  int cnt_;
};
