#pragma once
#include "Constant.h"
#include "CDataNode.h"

class CAttribute {
 public:
  CAttribute(double init);

  CAttribute& None(double value);
  CAttribute& Fire(double value);
  CAttribute& Aqua(double value);
  CAttribute& Thunder(double value);
  CAttribute& Flower(double value);
  CAttribute& Ice(double value);
  CAttribute& Wind(double value);

  double none_;
  double fire_;
  double aqua_;
  double thunder_;
  double flower_;
  double ice_;
  double wind_;

  CAttribute operator*(CAttribute a);
  CAttribute operator*(double a);
  CAttribute& operator*=(CAttribute a);
  CAttribute operator/(CAttribute a);
  CAttribute operator/(double a);
  CAttribute operator+(CAttribute a);
  CAttribute& operator+=(CAttribute a);
  CAttribute operator-(CAttribute a);
  bool IsZero();
  double Sum();
  void Load(const CDataNode*);
};
