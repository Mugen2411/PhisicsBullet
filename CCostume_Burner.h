#pragma once
#include "CCosutumeBase.h"
#include "CMover_Player.h"

class CCostume_Burner : public CCostumeBase {
 public:
  CCostume_Burner(std::string gid_);

  void WeakShot(CAttribute baseATK, CVector position, float angle);
  void ChargeShot(CAttribute baseATK, CVector position, float angle);

  CCostumeBase* Clone() { return new CCostume_Burner(gid_); }
};
