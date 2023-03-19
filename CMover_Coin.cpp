#include "CMover_Coin.h"
#include "CImageManager.h"
#include "CEffect_Bright.h"

const int CMover_Coin::kValue[4] = {100, 10, 1, -1};
const double CMover_Coin::kSize[3] = {40.0, 36.0, 32.0};
const double CMover_Coin::kMass[3] = {16.0, 4.0, 1.0};

CMover_Coin::CMover_Coin(CVector position, Type type)
    : CMover(
          kCoin, position, kSize[type],
          CVector(Constant::kPI2 * GetRand(64) / 64) * (GetRand(40) + 1) * 0.1,
          kMass[type], COF(0.08, 0.2, 0.05, 0.8, 0.1), 0),
      type_(type) {}

int CMover_Coin::Update() {
  animation_cnt_ += 0.2;
  if (animation_cnt_ > 3.0) animation_cnt_ = 0.0;
  return status_;
}

void CMover_Coin::Render() const {
  CImageManager::GetIns().Find("system_coin")->DrawRota(
      position_, 0.0f, 1.0f, Constant::kPriorityCoin,
      type_ * 4 + (int)animation_cnt_);
  CEffect_Bright::GetIns().Register(
      CEffect_Bright::BrightDesc(position_, size_, 64));
}
