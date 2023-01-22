#pragma once
#include "CField.h"
class CField_Void : public CField {
 public:
  CField_Void(std::string gid, CVector position_);
  CField* Clone(CVector position_);
};
