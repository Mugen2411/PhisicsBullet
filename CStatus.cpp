#include "CStatus.h"

#include <cmath>

CStatus::CStatus(int Level) : atk_cf_(1.0), hp_cf_(1.0) {
  this->level_ = Level;
  Calculate();
}

CStatus::CStatus(int Level, int ATK, int HP)
    : level_(Level),
      atk_(ATK),
      HP_(HP),
      maxHP_(HP),
      atk_cf_(1.0),
      hp_cf_(1.0) {}

CStatus::CStatus(int Level, double atkCF, double hpCF)
    : atk_cf_(atkCF), hp_cf_(hpCF) {
  this->level_ = Level;
  Calculate();
}

void CStatus::Load(const CDataNode* c) {}

void CStatus::Calculate() {
  atk_ = (100 * std::pow(1.05, level_) + 1 * level_) * atk_cf_;
  maxHP_ = (500 * std::pow(1.05, level_) + 5 * level_) * hp_cf_;
  HP_ = maxHP_;
}

CStatus CStatus::Test(int TargetLevel) {
  CStatus test(TargetLevel);
  return test - (*this);
}

CStatus CStatus::operator-(CStatus v) {
  return CStatus(level_ - v.level_, atk_ - v.atk_, HP_ - v.HP_);
}
