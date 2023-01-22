#include "CField_Wall_Log.h"

#include <DxLib.h>

CField_Wall_Log::CField_Wall_Log(std::string gid, CVector position_, int state_)
    : CField_Wall(gid, position_, COF().SetFrictionCF(0.9)),
      animation_cnt_(0.0),
      state_(state_),
      burning_time_(600) {}

void CField_Wall_Log::Update() {
  switch (state_) {
    case 0:
      if (temperature_ > 100) state_ = 1;
      is_wall_ = true;
      break;
    case 1:
      animation_cnt_ += 0.15;
      animation_cnt_ = std::fmod(animation_cnt_, 3);
      burning_time_--;
      // if (burning_time_ < 0)state_ = 2;
      damage_ = CAttribute(0.0).Fire(6.0);
      is_wall_ = false;
      break;
    case 2:
      damage_ = CAttribute(0.0);
      is_wall_ = false;
      break;
  }
}

void CField_Wall_Log::Render() const {
  switch (state_) {
    case 1:
      CImageManager::GetIns()
          .Find("effect_flame")
          ->DrawRotaFwithBlend(position_.x, position_.y, GetRand(16) / 256.0f,
                               1.0, 0xFFFFFF, CImageManager::kAdd, 216,
                               Constant::kPriorityEffect, (unsigned int)animation_cnt_);
      CImageManager::GetIns()
          .Find("Field_Grass")
          ->DrawRota(position_, 0.0, 1.0,
                     Constant::kPriorityDecoration, 4);
      break;
    case 0:
      CImageManager::GetIns()
          .Find("Field_Grass")
          ->DrawRota(position_, 0.0, 1.0, Constant::kPriorityWall,
                     4);
      break;
    case 2:
      CImageManager::GetIns()
          .Find("Field_Grass")
          ->DrawRota(position_, 0.0, 1.0, Constant::kPriorityWall,
                     5);
      break;
  }
}

CField* CField_Wall_Log::Clone(CVector position_) {
  return new CField_Wall_Log(gid_, position_, state_);
}
