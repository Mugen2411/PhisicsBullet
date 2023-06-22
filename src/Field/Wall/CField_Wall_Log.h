#pragma once
#include "CField_Wall.h"
class CField_Wall_Log : public CField_Wall {
 public:
  // state_ = 0:ëê 1:âäè„íÜ 2:è≈Ç∞
  CField_Wall_Log(std::string gid, CVector position_, int state_);

  void Update();
  void Render() const;

  CField* Clone(CVector position_);

 private:
  double animation_cnt_;
  int state_;
  int burning_time_;
};
