#pragma once
#include "CField_Wall.h"

class CField_Wall_Rock : public CField_Wall {
 public:
  CField_Wall_Rock(std::string gid, CVector position);

  void Update();
  void Render() const;

  CField* Clone(CVector position);
};