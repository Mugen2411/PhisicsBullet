#pragma once
#include "CCosutumeBase.h"
#include "CMover_Player.h"

class CCostume_Firefighter : public CCostumeBase {
 public:
  CCostume_Firefighter(std::string gid_);

  void WeakShot(CAttribute baseATK, CVector position, float angle);
  void ChargeShot(CAttribute baseATK, CVector position, float angle);

  CCostumeBase* Clone() { return new CCostume_Firefighter(gid_); }
};
