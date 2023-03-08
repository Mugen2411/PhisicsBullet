#pragma once
#include <cmath>
#include <string>
#include "CDataNode.h"

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
  static int GetMoneyToUpgrade(int now) { return (int)std::ceil(500 * std::powl(1.1, now)); }
  CStatus Test(int TargetLevel);
  CStatus operator-(CStatus v);
};

_NODISCARD inline std::string FloatToString(double _Val) {
  const auto _Len = static_cast<size_t>(_CSTD _scprintf("%.2f", _Val));
  std::string _Str(_Len, '\0');
  _CSTD sprintf_s(&_Str[0], _Len + 1, "%.2f", _Val);
  return _Str;
}