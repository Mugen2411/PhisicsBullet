#include "CPassiveSkill.h"

#include "CStatus.h"

CAttribute CPassiveSkill::GetAtkMult() {
  CAttribute ret(1.0);
  ret.none_ *= 1.0 + 0.01 * attr_atk_per_level_ * has_[kAtkNone];
  ret.fire_ *= 1.0 + 0.01 * attr_atk_per_level_ * has_[kAtkFire];
  ret.aqua_ *= 1.0 + 0.01 * attr_atk_per_level_ * has_[kAtkAqua];
  ret.thunder_ *= 1.0 + 0.01 * attr_atk_per_level_ * has_[kAtkThunder];
  ret.flower_ *= 1.0 + 0.01 * attr_atk_per_level_ * has_[kAtkFlower];
  ret.ice_ *= 1.0 + 0.01 * attr_atk_per_level_ * has_[kAtkIce];
  ret.wind_ *= 1.0 + 0.01 * attr_atk_per_level_ * has_[kAtkWind];
  ret *= CAttribute(1.0 + 0.01 * all_atk_per_level_ * has_[kAtkAll]);
  return ret;
}

CAttribute CPassiveSkill::GetDefMult() {
  CAttribute ret(1.0);
  ret.none_ *= 1.0 + 0.01 * attr_def_per_level_ * has_[kDefNone];
  ret.fire_ *= 1.0 + 0.01 * attr_def_per_level_ * has_[kDefFire];
  ret.aqua_ *= 1.0 + 0.01 * attr_def_per_level_ * has_[kDefAqua];
  ret.thunder_ *= 1.0 + 0.01 * attr_def_per_level_ * has_[kDefThunder];
  ret.flower_ *= 1.0 + 0.01 * attr_def_per_level_ * has_[kDefFlower];
  ret.ice_ *= 1.0 + 0.01 * attr_def_per_level_ * has_[kDefIce];
  ret.wind_ *= 1.0 + 0.01 * attr_def_per_level_ * has_[kDefWind];
  ret *= CAttribute(1.0 + 0.01 * all_def_per_level_ * has_[kDefAll]);
  return ret;
}

std::vector<int> CPassiveSkill::GetRandomList() {
  std::set<int> ret;
  std::vector<int> smp;
  int got[kMaxHasSkill];
  int p = 0;
  for (int i = 0; i < kSkillNum; i++) {
    if (has_[i] != 0) p++;
  }
  if (p < kMaxHasSkill) {
    for (int i = 0; i < kSkillNum; i++) {
      for (int j = 0; j < kMaxSkillLevel - has_[i]; j++) {
        ret.insert(i);
      }
    }
    std::sample(ret.begin(), ret.end(), std::back_inserter(smp), 3, engine_);
    return smp;
  }
  p = 0;
  for (int i = 0; i < kSkillNum; i++) {
    if (has_[i] != 0) {
      got[p] = i;
      p++;
    }
  }
  for (int i = 0; i < kSkillNum; i++) {
    p = 0;
    for (int j = 0; j < kMaxHasSkill; j++) {
      p |= (got[j] == i);
    }
    if (!p) continue;
    for (int j = 0; j < kMaxSkillLevel - has_[i]; j++) {
      ret.insert(i);
    }
  }
  std::sample(ret.begin(), ret.end(), std::back_inserter(smp), 3, engine_);
  return smp;
}

CTextDrawer::Text CPassiveSkill::GetText(int index) {
  CTextDrawer::Text ret("", CVector(32.0, 280.0), 0xFFFFFF, 0x000000, 0);
  std::string attr[7] = {"��", "��", "��", "��", "��", "�X", "��"};
  if (index <= kAtkWind) {
    ret.text_ = std::string("�^����") + attr[index % 7] +
                std::string("�����_���[�W��") +
                std::to_string(has_[index] * attr_atk_per_level_) +
                std::string("%��") +
                std::to_string((has_[index] + 1) * attr_atk_per_level_) +
                std::string("%��������B");
    return ret;
  }
  if (index <= kDefWind) {
    ret.text_ = std::string("�󂯂�") + attr[index % 7] +
                std::string("�����_���[�W��") +
                std::to_string(has_[index] * attr_def_per_level_) +
                std::string("%��") +
                std::to_string((has_[index] + 1) * attr_def_per_level_) +
                std::string("%�y������B");
    return ret;
  }
  if (index == kAtkAll) {
    ret.text_ = std::string("�^����") + std::string("�S�Ẵ_���[�W��") +
                std::to_string(has_[index] * all_atk_per_level_) +
                std::string("%��") +
                std::to_string((has_[index] + 1) * all_atk_per_level_) +
                std::string("%��������B");
    return ret;
  }
  if (index == kDefAll) {
    ret.text_ = std::string("�󂯂�") + std::string("�S�Ẵ_���[�W��") +
                std::to_string(has_[index] * all_def_per_level_) +
                std::string("%��") +
                std::to_string((has_[index] + 1) * all_def_per_level_) +
                std::string("%�y������B");
    return ret;
  }
  if (index == kHeal) {
    ret.text_ =
        std::string("HP�𖈕b") + FloatToString(has_[index] * heal_per_level_) +
        std::string("%��") + FloatToString((has_[index] + 1) * heal_per_level_) +
        std::string("%�񕜂���B");
    return ret;
  }
  if (index == kMoney) {
    ret.text_ = std::string("�l������S�ẴR�C����") +
                std::to_string(has_[index] * money_per_level_) +
                std::string("%��") +
                std::to_string((has_[index] + 1) * money_per_level_) +
                std::string("%��������B");
    return ret;
  }
  if (index == kCharge) {
    ret.text_ = std::string("�ˌ��̃`���[�W���x��") +
                std::to_string(has_[index] * charge_per_level_) +
                std::string("%��") +
                std::to_string((has_[index] + 1) * charge_per_level_) +
                std::string("%��������B");
    return ret;
  }
  if (index == kSpeed) {
    ret.text_ = std::string("���@�̍ō����x��") +
                std::to_string(has_[index] * speed_per_level_) +
                std::string("%��") +
                std::to_string((has_[index] + 1) * speed_per_level_) +
                std::string("%��������B");
    return ret;
  }
  if (index == kMaxHP) {
    ret.text_ = std::string("���@��HP�ő�l��") +
                std::to_string(has_[index] * maxHP_per_level_) +
                std::string("%��") +
                std::to_string((has_[index] + 1) * maxHP_per_level_) +
                std::string("%��������B");
    return ret;
  }
  if (index == kEnemyLevelUp) {
    ret.text_ = std::string("�G�̃��x����") + std::to_string(has_[index]) +
                std::string("�i�K��") + std::to_string((has_[index] + 1)) +
                std::string("�i�K��������B");
    return ret;
  }
  if (index == kEnemyAmountUp) {
    ret.text_ = std::string("�G�̏o������") +
                std::to_string(has_[index]) +
                std::string("�i�K��") +
                std::to_string((has_[index] + 1)) +
                std::string("�i�K��������B");
    return ret;
  }
  if (index == kEnemyValueUp) {
    ret.text_ = std::string("�G�̉��l��") +
                std::to_string(has_[index]) +
                std::string("�i�K��") +
                std::to_string((has_[index] + 1)) +
                std::string("�i�K��������B");
    return ret;
  }
  return ret;
}

CPassiveSkill::CPassiveSkill() : has_{0}, rnd_(), engine_(rnd_()) {}
