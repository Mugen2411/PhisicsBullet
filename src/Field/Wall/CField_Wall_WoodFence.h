#pragma once
#include "CField_Wall.h"
class CField_Wall_WoodFence : public CField_Wall {
 public:
  CField_Wall_WoodFence(std::string gid, CVector position_, int state_);

  void Update();
  void Render() const;

  CField* Clone(CVector position_);

 private:
  int state_;
};
