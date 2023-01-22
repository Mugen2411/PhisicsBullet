#pragma once
#include "CCosutumeBase.h"
#include "CMover_Player.h"

class CCostume_Swimsuit : public CCostumeBase {
 public:
  CCostume_Swimsuit(std::string gid_);

  void WeakShot(CAttribute baseATK, CVector position_, float angle);
  void ChargeShot(CAttribute baseATK, CVector position_, float angle);

  CCostumeBase* Clone() { return new CCostume_Swimsuit(gid_); }
};
