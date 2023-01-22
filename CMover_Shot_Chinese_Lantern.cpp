#include "CMover_Shot_Chinese_Lantern.h"

#include "CEffect_Bright.h"
#include "CImageManager.h"

CMover_Shot_Chinese_Lantern::CMover_Shot_Chinese_Lantern(CAttribute baseATK,
                                                         CVector position,
                                                         double angle)
    : CMover_ShotBase(
          baseATK, CAttribute(0.0).None(10).Fire(5), position, 24,
          CVector(angle + Constant::kPI2 / 6 * GetRand(10) * 0.1 - 0.5) * 16 *
              (GetRand(10) + 5) * 0.1,
          2, COF(0.001, 0.001, 0.2, 0.2), 0xFFCF00),
      init_(baseATK),
      cnt_(0),
      base_y_(0.0) {}

int CMover_Shot_Chinese_Lantern::Update() {
  cnt_++;
  double cf = max(1.0, min(10.0, velocity_.GetLength() / 5.0f));
  base_atk_ = init_ * cf;
  base_y_ = sin(Constant::kPI2 * Constant::kPerFrame * cnt_);
  if (cnt_ > 480) SetStatus(kDead);
  return status_;
}

void CMover_Shot_Chinese_Lantern::Render() const {
  CEffect_Bright::GetIns().Register(
      CEffect_Bright::BrightDesc(position_, 128.0 + GetRand(16) / 16.0, 96));
  CImageManager::GetIns()
      .Find("shot_chinese_lantern")
      ->DrawRota(position_ + CVector(0.0, base_y_), 0.0f, 1.0f,
                 Constant::kPriorityShot);
}
