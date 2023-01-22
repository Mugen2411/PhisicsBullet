#include "CMover_Enemy_Shimaenaga.h"

#include "CImageManager.h"

CMover_Enemy_Shimaenaga::CMover_Enemy_Shimaenaga(CVector position, int Level)
    : CMover_EnemyBase(40, Level, 0.1, 3.0, CAttribute(0.5), 300, 0x7F7F7F,
                       position, 0.0, 0.0, COF(0.1, 0.8, 0.8, 0.0)),
      animation_cnt_(0.0) {}

int CMover_Enemy_Shimaenaga::Update() {
  animation_cnt_ += 0.1;
  if (animation_cnt_ > 3) animation_cnt_ = 0.0;
  return status_;
}

void CMover_Enemy_Shimaenaga::Render() const {
  CImageManager::GetIns()
      .Find("enemy_shimaenaga")
      ->DrawRota(position_, 0.0, 1.0, Constant::kPriorityEnemy,
                 (unsigned int)animation_cnt_);
}

CMover_EnemyBase* CMover_Enemy_Shimaenaga::Clone(CVector position, int Level) {
  return new CMover_Enemy_Shimaenaga(position, Level);
}
