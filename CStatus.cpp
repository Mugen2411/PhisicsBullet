#include "CStatus.h"

#include <cmath>

CStatus::CStatus(int Level) : atkCF(1.0), hpCF(1.0) {
  this->Level = Level;
  Calculate();
}

CStatus::CStatus(int Level, int ATK, int HP)
    : Level(Level), ATK(ATK), HP(HP), MaxHP(HP), atkCF(1.0), hpCF(1.0) {}

CStatus::CStatus(int Level, double atkCF, double hpCF)
    : atkCF(atkCF), hpCF(hpCF) {
  this->Level = Level;
  Calculate();
}

void CStatus::Calculate() {
  ATK = (100 * std::pow(1.05, Level) + 1 * Level) * atkCF;
  MaxHP = (500 * std::pow(1.05, Level) + 5 * Level) * hpCF;
  HP = MaxHP;
}

CStatus CStatus::Test(int TargetLevel) {
  CStatus test(TargetLevel);
  return test - (*this);
}

CStatus CStatus::operator-(CStatus v) {
  return CStatus(Level - v.Level, ATK - v.ATK, HP - v.HP);
}
