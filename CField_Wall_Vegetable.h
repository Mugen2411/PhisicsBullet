#pragma once
#include "CField_Wall.h"

class CField_Wall_Vegetable : public CField_Wall {
  int state;

 public:
  CField_Wall_Vegetable(std::string gid, CVector position, int state);

  void Update();
  void Render() const;

  CField* Clone(CVector position);
};
