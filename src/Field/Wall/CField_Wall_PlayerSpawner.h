#pragma once
#include "Field/CField.h"

class CField_Wall_PlayerSpawner : public CField {
 public:
  CField_Wall_PlayerSpawner(std::string gid, CVector position_);
  void Update();
  void Render() const;

  CField* Clone(CVector position_);
};