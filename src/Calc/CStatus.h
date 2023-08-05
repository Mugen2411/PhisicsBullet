#pragma once
#include <cmath>
#include <string>
#include "Data/CDataNode.h"

class CStatus {
 public:
  int level_;
  double atk_;
  double HP_;
  double maxHP_;
  double atk_cf_;
  double hp_cf_;

  CStatus(int Level);
  CStatus(int Level, int ATK, int HP);
  CStatus(int Level, double atkCF, double hpCF);

  void Load(const CDataNode* c);

  void Calculate();
  static double GetMoneyToUpgrade(int now) { return std::ceil(150 * std::powl(1.0502, now)* std::pow(1.3, (int)(now / 15)) *
         std::pow(1.8, (int)(now / 60))); }
  CStatus Test(int TargetLevel);
  CStatus operator-(CStatus v);
};

_NODISCARD inline std::string FloatToString(double _Val) {
  const auto _Len = static_cast<size_t>(_CSTD _scprintf("%.2f", _Val));
  std::string _Str(_Len, '\0');
  _CSTD sprintf_s(&_Str[0], _Len + 1, "%.2f", _Val);
  return _Str;
}