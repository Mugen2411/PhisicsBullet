#pragma once
#include "CField.h"

class CField_Wall : public CField {
 public:
  CField_Wall(std::string gid_, CVector position_, COF cofs);

  bool Hit(CMover*) override;
};
