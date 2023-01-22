#include "CEffect_EnemyDelete.h"

#include "CImageManager.h"

CEffect_EnemyDelete::CEffect_EnemyDelete(CVector position_, double size,
                                         int color, int duration)
    : CEffect(position_),
      size_(size),
      color_(color),
      cnt_(0),
      animation_cnt_(0.0),
      duration_(duration) {}

void CEffect_EnemyDelete::Update() {
  animation_cnt_ += 8.0 / duration_;
  cnt_++;
  if (cnt_ > duration_ - 1) status_ = 1;
}

void CEffect_EnemyDelete::Render() const {
  CImageManager::GetIns()
      .Find("effect_bulletdelete")
      ->DrawRotaFwithBlend(
          position_.x, position_.y, 0,
          float(size_ * (1 - std::powl(1 - (double)cnt_ / duration_, 2))) / 16.0f, color_,
          CImageManager::kNone, 255, Constant::kPriorityEffect, (uint32_t)animation_cnt_);
  CImageManager::GetIns()
      .Find("effect_bulletdelete")
      ->DrawRotaFwithBlend(
          position_.x, position_.y, 0,
          float(size_ * (1 - std::powl(1 - (double)cnt_ / duration_, 2))) / 16.0f,
          0xFFFFFF, CImageManager::kAdd, 255, Constant::kPriorityEffect + 1,
          (uint32_t)animation_cnt_);
}
