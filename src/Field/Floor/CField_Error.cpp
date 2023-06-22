#include "CField_Error.h"

#include "Graphic/Image/CImageManager.h"

CField_Error::CField_Error(std::string gid, CVector position_)
    : CField(gid, position_, CVector(32, 32), COF(), 0, CAttribute(0.0)) {}

void CField_Error::Update() {}

void CField_Error::Render() const {
  CImageManager::GetIns()
      .Find("Field_Error")
      ->DrawRota(position_, 0.0f, 1.0f, -1);
}

CField* CField_Error::Clone(CVector position_) {
  return new CField_Error(gid_, position_);
}
