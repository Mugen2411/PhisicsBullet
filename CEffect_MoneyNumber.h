#pragma once
#include "CEffect.h"
class CEffect_MoneyNumber : public CEffect {
 public:
  CEffect_MoneyNumber(CVector position_, int num);

  void Update();
  void Render() const;

 private:
  int num_;
  double dy_;
  int cnt_;
};
