#include "CPassiveSkill.h"

#include "CStatus.h"

CAttribute CPassiveSkill::getATKmult() {
  CAttribute ret(1.0);
  ret.None *= 1.0 + 0.01 * attrATKperLEVEL * has[ATK_NONE];
  ret.Fire *= 1.0 + 0.01 * attrATKperLEVEL * has[ATK_FIRE];
  ret.Aqua *= 1.0 + 0.01 * attrATKperLEVEL * has[ATK_AQUA];
  ret.Thunder *= 1.0 + 0.01 * attrATKperLEVEL * has[ATK_THUNDER];
  ret.Flower *= 1.0 + 0.01 * attrATKperLEVEL * has[ATK_FLOWER];
  ret.Ice *= 1.0 + 0.01 * attrATKperLEVEL * has[ATK_ICE];
  ret.Wind *= 1.0 + 0.01 * attrATKperLEVEL * has[ATK_WIND];
  ret *= CAttribute(1.0 + 0.01 * allATKperLEVEL * has[ATK_ALL]);
  return ret;
}

CAttribute CPassiveSkill::getDEFmult() {
  CAttribute ret(1.0);
  ret.None *= 1.0 + 0.01 * attrDEFperLEVEL * has[DEF_NONE];
  ret.Fire *= 1.0 + 0.01 * attrDEFperLEVEL * has[DEF_FIRE];
  ret.Aqua *= 1.0 + 0.01 * attrDEFperLEVEL * has[DEF_AQUA];
  ret.Thunder *= 1.0 + 0.01 * attrDEFperLEVEL * has[DEF_THUNDER];
  ret.Flower *= 1.0 + 0.01 * attrDEFperLEVEL * has[DEF_FLOWER];
  ret.Ice *= 1.0 + 0.01 * attrDEFperLEVEL * has[DEF_ICE];
  ret.Wind *= 1.0 + 0.01 * attrDEFperLEVEL * has[DEF_WIND];
  ret *= CAttribute(1.0 + 0.01 * allDEFperLEVEL * has[DEF_ALL]);
  return ret;
}

std::vector<int> CPassiveSkill::getRandomList() {
  std::set<int> ret;
  std::vector<int> smp;
  int got[5];
  int p = 0;
  for (int i = 0; i < 21; i++) {
    if (has[i] != 0) p++;
  }
  if (p < 5) {
    for (int i = 0; i < 21; i++) {
      for (int j = 0; j < 5 - has[i]; j++) {
        ret.insert(i);
      }
    }
    std::sample(ret.begin(), ret.end(), std::back_inserter(smp), 3, engine);
    return smp;
  }
  p = 0;
  for (int i = 0; i < 21; i++) {
    if (has[i] != 0) {
      got[p] = i;
      p++;
    }
  }
  for (int i = 0; i < 21; i++) {
    p = 0;
    for (int j = 0; j < 5; j++) {
      p |= (got[j] == i);
    }
    if (!p) continue;
    for (int j = 0; j < 5 - has[i]; j++) {
      ret.insert(i);
    }
  }
  std::sample(ret.begin(), ret.end(), std::back_inserter(smp), 3, engine);
  return smp;
}

CTextDrawer::Text CPassiveSkill::getText(int index) {
  CTextDrawer::Text ret("", CVector(32.0, 280.0), 0xFFFFFF, 0x000000, 0);
  std::string attr[7] = {"無", "炎", "水", "雷", "花", "氷", "風"};
  if (index <= ATK_WIND) {
    ret.text = std::string("与える") + attr[index % 7] +
               std::string("属性ダメージを") +
               std::to_string(has[index] * attrATKperLEVEL) +
               std::string("%→") +
               std::to_string((has[index] + 1) * attrATKperLEVEL) +
               std::string("%増加する。");
    return ret;
  }
  if (index <= DEF_WIND) {
    ret.text = std::string("受ける") + attr[index % 7] +
               std::string("属性ダメージを") +
               std::to_string(has[index] * attrDEFperLEVEL) +
               std::string("%→") +
               std::to_string((has[index] + 1) * attrDEFperLEVEL) +
               std::string("%軽減する。");
    return ret;
  }
  if (index == ATK_ALL) {
    ret.text = std::string("与える") + std::string("全てのダメージを") +
               std::to_string(has[index] * allATKperLEVEL) + std::string("%→") +
               std::to_string((has[index] + 1) * allATKperLEVEL) +
               std::string("%増加する。");
    return ret;
  }
  if (index == DEF_ALL) {
    ret.text = std::string("受ける") + std::string("全てのダメージを") +
               std::to_string(has[index] * allDEFperLEVEL) + std::string("%→") +
               std::to_string((has[index] + 1) * allDEFperLEVEL) +
               std::string("%軽減する。");
    return ret;
  }
  if (index == HEAL) {
    ret.text = std::string("HPを毎秒") +
               floating_to_string(has[index] * healPerLEVEL) +
               std::string("%→") +
               floating_to_string((has[index] + 1) * healPerLEVEL) +
               std::string("%回復する。");
    return ret;
  }
  if (index == MONEY) {
    ret.text = std::string("獲得する全てのコインを") +
               std::to_string(has[index] * moneyPerLEVEL) + std::string("%→") +
               std::to_string((has[index] + 1) * moneyPerLEVEL) +
               std::string("%増加する。");
    return ret;
  }
  if (index == CHARGE) {
    ret.text = std::string("射撃のチャージ速度を") +
               std::to_string(has[index] * chargePerLEVEL) + std::string("%→") +
               std::to_string((has[index] + 1) * chargePerLEVEL) +
               std::string("%増加する。");
    return ret;
  }
  if (index == SPEED) {
    ret.text = std::string("自機の最高速度を") +
               std::to_string(has[index] * speedPerLEVEL) + std::string("%→") +
               std::to_string((has[index] + 1) * speedPerLEVEL) +
               std::string("%増加する。");
    return ret;
  }
  if (index == MAXHP) {
    ret.text = std::string("自機のHP最大値を") +
               std::to_string(has[index] * maxHPperLEVEL) + std::string("%→") +
               std::to_string((has[index] + 1) * maxHPperLEVEL) +
               std::string("%増加する。");
    return ret;
  }
  return ret;
}

CPassiveSkill::CPassiveSkill() : has{0}, rnd(), engine(rnd()) {}
