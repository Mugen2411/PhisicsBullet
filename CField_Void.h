#pragma once
#include "CField.h"
class CField_Void : public CField {
 public:
  CField_Void(std::string gid, CVector position);
  CField* Clone(CVector position);
};
