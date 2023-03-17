#include "CField_Lava.h"

#include <DxLib.h>

#include "CEffect_Bright.h"

CField_Lava::CField_Lava(std::string gid, CVector position_, double temperature,
                         int direction)
    : CField(gid, position_, CVector(32.0, 32.0),
             COF().SetFrictionCF(0.6).SetAirResCF(0.9),
             temperature, CAttribute(0.0)),
      cnt_(0),
      kAnimDur(180),
      direction_(direction) {}

void CField_Lava::Update() {
  cnt_++;
  if (temperature_ < 0) {
    cofs_.SetWaterResCF(0.0).SetFrictionCF(0.6);
    damage_ = CAttribute(0.0);
  } else {
    cofs_.SetWaterResCF(0.9).SetFrictionCF(0.2);
    damage_ = CAttribute(0.0).None(0.0).Fire(15.0);
  }
}

void CField_Lava::Render() const {
  int brightness = int(sin(Constant::kPI2 * (double)cnt_ / kAnimDur) * 0x3F);
  if (temperature_ < 0)
    CImageManager::GetIns()
        .Find("Field_Lava")
        ->DrawRota(position_, 0.0, 1.0, Constant::kPriorityField, 1);
  else {
    CEffect_Bright::GetIns().Register(
        CEffect_Bright::BrightDesc(position_, 512 - GetRand(16), 64));
    CImageManager::GetIns()
        .Find("Field_Lava")
        ->DrawRota(position_, 0.0, 1.0, Constant::kPriorityField, 0);
    CImageManager::GetIns()
        .Find("Field_Lava")
        ->DrawRotaFwithBlend(position_.x_, position_.y_, 0.0, 1.01f, 0xFFFFFF,
                             CImageManager::BlendMode::kAdd, brightness,
                             Constant::kPriorityField + 2, 2);
    if (direction_ & 1) {
      CImageManager::GetIns()
          .Find("Field_Lava")
          ->DrawRota(
              position_ +
                  CVector(0.0,
                          -14.0 - sin(Constant::kPI2 / kAnimDur * cnt_) * 1.99),
              Constant::kPI2 / 4 * 0, 1.0, Constant::kPriorityField + 1, 3);
      CImageManager::GetIns()
          .Find("Field_Lava")
          ->DrawRotaFwithBlend(position_.x_,
                               position_.y_ - 14.0 -
                                   sin(Constant::kPI2 / kAnimDur * cnt_) * 1.99,
                               Constant::kPI2 / 4 * 0, 1.0, 0xFFFFFF,
                               CImageManager::BlendMode::kAdd, brightness,
                               Constant::kPriorityField + 2, 4);
    }
    if (direction_ & 2) {
      CImageManager::GetIns()
          .Find("Field_Lava")
          ->DrawRota(
              position_ +
                  CVector(14.0 + sin(Constant::kPI2 / kAnimDur * cnt_) * 1.99,
                          0.0),
              Constant::kPI2 / 4 * 1, 1.0, Constant::kPriorityField + 1, 3);
      CImageManager::GetIns()
          .Find("Field_Lava")
          ->DrawRotaFwithBlend(position_.x_ + 14.0 +
                                   sin(Constant::kPI2 / kAnimDur * cnt_) * 1.99,
                               position_.y_, Constant::kPI2 / 4 * 1, 1.0,
                               0xFFFFFF, CImageManager::BlendMode::kAdd,
                               brightness, Constant::kPriorityField + 2, 4);
    }
    if (direction_ & 4) {
      CImageManager::GetIns()
          .Find("Field_Lava")
          ->DrawRota(
              position_ +
                  CVector(0.0,
                          14.0 + sin(Constant::kPI2 / kAnimDur * cnt_) * 1.99),
              Constant::kPI2 / 4 * 2, 1.0, Constant::kPriorityField + 1, 3);
      CImageManager::GetIns()
          .Find("Field_Lava")
          ->DrawRotaFwithBlend(position_.x_,
                               position_.y_ + 14.0 +
                                   sin(Constant::kPI2 / kAnimDur * cnt_) * 1.99,
                               Constant::kPI2 / 4 * 2, 1.0, 0xFFFFFF,
                               CImageManager::BlendMode::kAdd, brightness,
                               Constant::kPriorityField + 2, 4);
    }
    if (direction_ & 8) {
      CImageManager::GetIns()
          .Find("Field_Lava")
          ->DrawRota(
              position_ +
                  CVector(-14.0 - sin(Constant::kPI2 / kAnimDur * cnt_) * 1.99,
                          0.0),
              Constant::kPI2 / 4 * 3, 1.0, Constant::kPriorityField + 1, 3);
      CImageManager::GetIns()
          .Find("Field_Lava")
          ->DrawRotaFwithBlend(position_.x_ - 14.0 -
                                   sin(Constant::kPI2 / kAnimDur * cnt_) * 1.99,
                               position_.y_, Constant::kPI2 / 4 * 3, 1.0,
                               0xFFFFFF, CImageManager::BlendMode::kAdd,
                               brightness, Constant::kPriorityField + 2, 4);
    }
  }
}

CField* CField_Lava::Clone(CVector position_) {
  return new CField_Lava(gid_, position_, temperature_, direction_);
}
