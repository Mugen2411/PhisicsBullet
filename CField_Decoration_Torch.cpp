#include "CField_Decoration_Torch.h"

#include <DxLib.h>

#include "CEffect_Bright.h"

CField_Decoration_Torch::CField_Decoration_Torch(std::string gid,
                                                 CVector position_)
    : CField_Wall(gid, position_, COF().SetFrictionCF(0.9)),
      animation_cnt_(0.0),
      state_(0),
      burning_time_(600) {}

void CField_Decoration_Torch::Update() {
  animation_cnt_ += 0.15;
  animation_cnt_ = std::fmod(animation_cnt_, 3);
  burning_time_--;
  if (state_ == 1)
    damage_ = CAttribute(0.0).Fire(4.0);
  else
    damage_ = CAttribute(0.0);
  is_wall_ = false;
}

void CField_Decoration_Torch::Render() const {
  if (state_ == 1) {
    CEffect_Bright::GetIns().Register(
        CEffect_Bright::BrightDesc(position_, 512 - GetRand(16), 216));
    CImageManager::GetIns()
        .Find("effect_bornfire")
        ->DrawRotaFwithBlend(position_.x, position_.y, GetRand(16) / 256.0f, 1.0,
                             0xFFFFFF, CImageManager::kAdd, 216,
                             Constant::kPriorityEffect, (uint32_t)animation_cnt_);
  }
  CImageManager::GetIns()
      .Find("Field_Cave")
      ->DrawRota(position_, 0.0, 1.0,
                 Constant::kPriorityDecoration, 4);
}

CField* CField_Decoration_Torch::Clone(CVector position_) {
  return new CField_Decoration_Torch(gid_, position_);
}
