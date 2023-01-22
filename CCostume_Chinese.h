#pragma once
#include "CCosutumeBase.h"
#include "CMover_Player.h"

class CCostume_Chinese : public CCostumeBase {
 public:
  CCostume_Chinese(std::string gid_);

  void WeakShot(CAttribute baseATK, CVector position, float angle);
  void ChargeShot(CAttribute baseATK, CVector position, float angle);

  CCostumeBase* Clone() { return new CCostume_Chinese(gid_); }
};
