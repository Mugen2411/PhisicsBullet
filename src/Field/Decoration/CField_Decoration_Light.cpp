#include "CField_Decoration_Light.h"

#include <DxLib.h>

#include "Effect/CEffect_Bright.h"

CField_Decoration_Light::CField_Decoration_Light(std::string gid,
                                                 CVector position_)
    : CField_Wall(gid, position_, COF().SetFrictionCF(0.6)), state_(0) {}

void CField_Decoration_Light::Update() {
  if (state_ == 0)
    damage_ = CAttribute(0.0).Thunder(4.0);
  else
    damage_ = CAttribute(0.0);
  is_wall_ = false;
}

void CField_Decoration_Light::Render() const {
  if (state_ == 1) {
    CEffect_Bright::GetIns().Register(
        CEffect_Bright::BrightDesc(position_, 512 - GetRand(16), 216));
  }
  CImageManager::GetIns()
      .Find("Field_Cave")
      ->DrawRota(position_, 0.0, 1.0,
                 Constant::kPriorityDecoration, 5);
}

CField* CField_Decoration_Light::Clone(CVector position_) {
  return new CField_Decoration_Light(gid_, position_);
}
