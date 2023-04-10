#pragma once
#include <algorithm>
#include <random>
#include <set>

#include "CAttribute.h"
#include "CTextDrawer.h"
#include "Singleton.h"

class CPassiveSkill : public Singleton<CPassiveSkill> {
 public:
  CAttribute GetAtkMult();
  CAttribute GetDefMult();
  double GetHealRatio() { return 0.01 * heal_per_level_ * has_[kHeal]; }
  double GetMaxHPmult() { return 1.0 + 0.01 * maxHP_per_level_ * has_[kMaxHP]; }
  double GetMoneyMult() { return 1.0 + 0.01 * money_per_level_ * has_[kMoney]; }
  double GetChargeMult() {
    return 1.0 + 0.01 * charge_per_level_ * has_[kCharge];
  }
  double GetSpeedMult() { return 1.0 + 0.01 * speed_per_level_ * has_[kSpeed]; }
  int GetEnemyLevelAdd() {
    return has_[kEnemyLevelUp - 1] * (has_[kEnemyLevelUp]) / 2;
  }
  int GetEnemyAmount(int baseAmount) {
    int add = has_[kEnemyAmountUp] == 5;
    double mult = 1.0 + has_[kEnemyAmountUp] * kEnemyAmountUp * 0.01;
    return (int)round(baseAmount*mult) + add;
  }
  void Reset() {
    for (auto& i : has_) {
      i = 0;
    }
    /* 
    has_[kEnemyAmountUp] = 5;
    has_[kMoney] = 5;
    has_[kAtkAll] = 5;
    has_[kAtkFire] = 5;
    has_[kAtkThunder] = 5;
    has_[kHeal] = 5;
    has_[kMaxHP] = 5;
    */
  }

  std::vector<int> GetRandomList();

  std::vector<int> GetGotSkillList() {
    std::vector<int> ret;
    for (int i = 0; i < kSkillNum; i++) {
      if (has_[i] != 0) ret.push_back(i);
    }
    return ret;
  }
  std::vector<int> GetGotSkillLevelList() {
    std::vector<int> ret;
    for (int i = 0; i < kSkillNum; i++) {
      if (has_[i] != 0) ret.push_back(has_[i]);
    }
    return ret;
  }

  void Add(int index) { has_[index] = (std::min)(++has_[index], 5); }

  CTextDrawer::Text GetText(int index);
  static const int kMaxHasSkill = 7;
  static const int kMaxSkillLevel = 5;

 protected:
  static const int kSkillNum = 23;
  int has_[7 + 7 + 2 + 5 + 2];
  enum {
    kAtkNone,
    kAtkFire,
    kAtkAqua,
    kAtkThunder,
    kAtkFlower,
    kAtkIce,
    kAtkWind,
    kDefNone,
    kDefFire,
    kDefAqua,
    kDefThunder,
    kDefFlower,
    kDefIce,
    kDefWind,
    kAtkAll,
    kDefAll,
    kHeal,
    kMoney,
    kCharge,
    kSpeed,
    kMaxHP,
    kEnemyLevelUp,
    kEnemyAmountUp
  };
  const int attr_atk_per_level_ = 15;
  const int attr_def_per_level_ = 15;
  const int all_atk_per_level_ = 6;
  const int all_def_per_level_ = 6;
  const double heal_per_level_ = 0.4;
  const int money_per_level_ = 10;
  const int charge_per_level_ = 2;
  const int speed_per_level_ = 2;
  const int maxHP_per_level_ = 10;
  const int enemyAmount_per_level_ = 10;

  std::random_device rnd_;
  std::mt19937 engine_;
  CPassiveSkill();

  friend Singleton<CPassiveSkill>;
};