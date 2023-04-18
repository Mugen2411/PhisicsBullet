#include "CMover_Enemy_Shimaenaga.h"

#include "CImageManager.h"

CMover_Enemy_Shimaenaga::CMover_Enemy_Shimaenaga(CVector position, int Level)
    : CMover_EnemyBase("E_Shimaenaga", Level, position){}

int CMover_Enemy_Shimaenaga::Update() {
  return status_;
}

void CMover_Enemy_Shimaenaga::Render() const {
  CImageManager::GetIns()
      .Find("enemy_shimaenaga")
      ->DrawRota(position_, 0.0, 1.0, Constant::kPriorityEnemy,
                 (unsigned int)animCnt_.Get());
}

CMover_EnemyBase* CMover_Enemy_Shimaenaga::Clone(CVector position, int Level) {
  return new CMover_Enemy_Shimaenaga(position, Level);
}
