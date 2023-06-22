#pragma once
#include "CCosutumeBase.h"
#include "Mover/CMover_Player.h"

class CCostume_Archer_Thunder : public CCostumeBase {
 public:
  CCostume_Archer_Thunder(std::string gid_);

  void WeakShot(CAttribute baseATK, CVector position, float angle);
  void ChargeShot(CAttribute baseATK, CVector position, float angle);

  CCostumeBase* Clone() { return new CCostume_Archer_Thunder(gid_); }
};
