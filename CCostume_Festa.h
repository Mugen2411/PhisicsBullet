#pragma once
#include "CCosutumeBase.h"
#include "CMover_Player.h"

class CCostume_Festa : public CCostumeBase {
 public:
  CCostume_Festa(std::string gid_);

  void WeakShot(CAttribute baseATK, CVector position, float angle);
  void ChargeShot(CAttribute baseATK, CVector position, float angle);

  CCostumeBase* Clone() { return new CCostume_Festa(gid_); }
};
