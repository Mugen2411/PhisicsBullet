#include "CField_Void.h"

CField_Void::CField_Void(std::string gid, CVector position_)
    : CField(gid, position_, CVector(32, 32), COF(), 0) {}

CField* CField_Void::Clone(CVector position_) {
  return new CField_Void(gid_, position_);
}
