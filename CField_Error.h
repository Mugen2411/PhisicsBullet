#pragma once
#include "CField.h"
class CField_Error : public CField {
 public:
  CField_Error(std::string gid, CVector position_);
  void Update();
  void Render() const;

  CField* Clone(CVector position_);
};
