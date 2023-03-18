#include "CField_Grass.h"

#include <DxLib.h>

#include "CEffect_Bright.h"

CField_Grass::CField_Grass(std::string gid, CVector position_)
    : CField(gid, position_, CVector(32.0, 32.0),
             COF().SetFrictionCF(0.95).SetAirResCF(0.2), 0),
      animation_cnt_(0),
      burning_time_(0),
      state_(0),
      fertile_(0) {
  if (GetRand(3) != 0)
    decoration_ = 0;
  else {
    if (GetRand(1) == 0)
      decoration_ = 1;
    else
      decoration_ = 2;
  }
}

void CField_Grass::Update() {
  switch (state_) {
    case 0:
      if (temperature_ > 100.0) {
        state_ = 1;
        burning_time_ = 600;
      }
      break;
    case 1:
      damage_.Fire(8.0);
      animation_cnt_ += 0.15;
      animation_cnt_ = std::fmod(animation_cnt_, 3);
      burning_time_--;
      if (burning_time_ < 0 || temperature_ < 0) {
        state_ = 2;
      }
      break;
    case 2:
      damage_ = CAttribute(0.0);
      if (fertile_ > 200.0) {
        state_ = 0;
        temperature_ = 0;
      }
      break;
  }
}

void CField_Grass::Render() const {
  if (state_ == 0)
    CImageManager::GetIns()
        .Find("Field_Grass")
        ->DrawRota(position_, 0.0, 1.0, Constant::kPriorityField,
                   decoration_);
  else
    CImageManager::GetIns()
        .Find("Field_Grass")
        ->DrawRota(position_, 0.0, 1.0, Constant::kPriorityField,
                   28);

  if (state_ == 1) {
    CEffect_Bright::GetIns().Register(
        CEffect_Bright::BrightDesc(position_, 128 - GetRand(16), 216));
    CImageManager::GetIns()
        .Find("effect_flame")
        ->DrawRotaFwithBlend(position_.x_, position_.y_, GetRand(16) / 256.0f, 1.0,
                             0xFFFFFF, CImageManager::kAdd, 216,
                             Constant::kPriorityEffect, (unsigned int)animation_cnt_);
  }
}

CField* CField_Grass::Clone(CVector position_) {
  return new CField_Grass(gid_, position_);
}
