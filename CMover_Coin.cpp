#include "CMover_Coin.h"

#include "CEffect_Bright.h"
#include "CImageManager.h"

const double CMover_Coin::kValue[26] = {
    1e12, 5e11, 1e11, 5e10, 1e10, 5e9, 1e9, 5e8, 1e8, 5e7, 1e7, 5e6, 1e6,
    5e5,  1e5,  5e4,  1e4,  5e3,  1e3, 5e2, 1e2, 50,  10,  5,   1,   -1};
const double CMover_Coin::kSize[25] = {32.0, 30.0, 28.0, 26.0, 24.0, 26.0, 24.0,
                                       26.0, 24.0, 26.0, 24.0, 26.0, 24.0, 26.0,
                                       24.0, 26.0, 24.0, 26.0, 24.0, 22.0, 20.0,
                                       18.0, 16.0, 14.0, 12.0};
const double CMover_Coin::kMass[25] = {36.0, 25.0, 25.0, 16.0, 16.0, 16.0, 16.0,
                                       16.0, 16.0, 16.0, 16.0, 16.0, 16.0, 16.0,
                                       16.0, 16.0, 16.0, 16.0, 16.0, 9.0,  9.0,
                                       4.0,  4.0,  1.0,  1.0};

CMover_Coin::CMover_Coin(CVector position, Type type)
    : CMover(kCoin, position, kSize[type],
             CVector(Constant::kPI2 * GetRand(128) / 128) * (GetRand(40) + 1) *
                 0.05,
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
      ->DrawRota(position_ + CVector(0.0, z), 0.0f, 1.0f,
                 Constant::kPriorityCoin, type_ * 5 + (int)animation_cnt_);
  CImageManager::GetIns()
      .Find("system_coin")
      ->DrawRota(position_ + CVector(0.0, 1.0), 0.0f, 1.0f,
                 Constant::kPriorityCoin - 1, type_ * 5 + 4);
  CEffect_Bright::GetIns().Register(
      CEffect_Bright::BrightDesc(position_, size_, 64));
}
