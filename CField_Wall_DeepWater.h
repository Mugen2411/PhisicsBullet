#pragma once
#include "CField_Wall.h"
class CField_Wall_DeepWater : public CField_Wall {
 public:
  CField_Wall_DeepWater(std::string gid, CVector position);

  void Update();
  void Render() const;

  CField* Clone(CVector position);
};