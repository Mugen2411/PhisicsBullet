#include "CMover_Coin.h"

#include "CEffect_Bright.h"
#include "CImageManager.h"

const int CMover_Coin::kValue[6] = {10000, 1000, 100, 10, 1, -1};
const double CMover_Coin::kSize[5] = {48.0, 44.0, 40.0, 36.0, 32.0};
const double CMover_Coin::kMass[5] = {25.0, 16.0, 9.0, 4.0, 1.0};

CMover_Coin::CMover_Coin(CVector position, Type type)
    : CMover(
          kCoin, position, kSize[type],
          CVector(Constant::kPI2 * GetRand(64) / 64) * (GetRand(40) + 1) * 0.1,
          kMass[type], COF(0.08, 0.2, 0.05, 0.8, 0.1), 0),
      type_(type),
      z(0.0),
      dz(GetRand(60) * -0.1) {}

int CMover_Coin::Update() {
  dz += 0.3;
  z += dz;
  if (z > 0.0) {
    z = 0.0;
    dz *= -0.7;
    if (abs(dz) < 0.05) dz = 0.0;
  }
  animation_cnt_ += 0.2;
  if (animation_cnt_ > 3.0) animation_cnt_ = 0.0;
  return status_;
}

void CMover_Coin::Render() const {
  CImageManager::GetIns()
      .Find("system_coin")
      ->DrawRota(position_ + CVector(0.0, z), 0.0f, 1.0f, Constant::kPriorityCoin,
                 type_ * 5 + (int)animation_cnt_);
  CImageManager::GetIns()
      .Find("system_coin")
      ->DrawRota(position_ + CVector(0.0, 1.0), 0.0f, 1.0f,
                 Constant::kPriorityCoin-1, type_ * 5 + 4);
  CEffect_Bright::GetIns().Register(
      CEffect_Bright::BrightDesc(position_, size_, 64));
}
