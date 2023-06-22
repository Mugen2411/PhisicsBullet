#pragma once
#include "CField_Wall.h"

class CField_Wall_IceRock : public CField_Wall {
 public:
  CField_Wall_IceRock(std::string gid, CVector position_);

  void Update();
  void Render() const;

  CField* Clone(CVector position_);
};