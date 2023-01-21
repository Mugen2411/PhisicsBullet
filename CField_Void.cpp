#include "CField_Void.h"

CField_Void::CField_Void(std::string gid, CVector position)
    : CField(gid, position, CVector(32, 32), COF(), 0) {}

CField* CField_Void::Clone(CVector position) {
  return new CField_Void(GID, position);
}
