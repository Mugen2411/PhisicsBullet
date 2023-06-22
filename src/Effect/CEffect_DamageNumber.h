#pragma once
#include "CEffect.h"
#include "Graphic/Draw/CNumberDrawer.h"

class CEffect_DamageNumber : public CEffect {
 public:
  CEffect_DamageNumber(CVector position_, double num, int type, int Style = 0);

  void Update();
  void Render() const;

 private:
  double dy_;
  int cnt_ = 0;
  double num_;
  int type_ = 0;
  int style_ = 0;

  CNumberDrawer number_drawer_;
};
