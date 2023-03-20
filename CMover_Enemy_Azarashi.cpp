#include "CMover_Enemy_Azarashi.h"

#include "CDataLoader.h"
#include "CImageManager.h"
#include "CMover_Bullet_Ice.h"
#include "CNumberDrawer.h"
#include "CSoundManager.h"

CMover_Enemy_Azarashi::CMover_Enemy_Azarashi(CVector position, int Level)
    : CMover_EnemyBase("E_Azarashi", Level, position), test_dest_(0.0, 0.0) {}

int CMover_Enemy_Azarashi::Update() {
  switch (state_) {
    case 0:
      if (cnt_ % 60 == 0) {
        if (GetRand(5) == 0) {
          FindTargetByDistance(8);
          state_ = 2;
          cnt_ = 0;
        } else
          FindRoute(5);
      }
      if (!route_.empty()) {
        Move_on_Route();
      } else {
        CVector ppos = med_->GetPlayerPosition();
        for (int i = 0; i < 3; i++)
          med_->RegisterMover(std::make_shared<CMover_Bullet_Ice>(
              base_params_, position_, (ppos - position_).GetAngle()-Constant::kPI2/8*(i-1), 3.0));
        CSoundManager::GetIns()
            .Find("pretty_throw")
            ->Play(CSound::PlayType::kBack);
        cnt_ = 0;
        state_ = 1;
        break;
      }
      cnt_++;
      animation_cnt_ += 0.3;
      if (animation_cnt_ > 4) animation_cnt_ = 0;
      break;
    case 1:
      if (cnt_ > 50) {
        state_ = 0;
        cnt_ = 0;
        break;
      }
      cnt_++;
      break;
    case 2:
      if (!route_.empty()) {
        Move_on_Route();
      } else {
        state_ = 0;
        cnt_ = 0;
      }
      if ((med_->GetPlayerPosition() - position_).GetLength2() >
              (32 * 6 * 32 * 6) &&
          cnt_ % 90 == 0)
        FindTargetByDistance(6);
      cnt_++;
      animation_cnt_ += 0.3;
      if (animation_cnt_ > 4) animation_cnt_ = 0;
      break;
    case -1:
      animation_cnt_ += 0.1;
      if (animation_cnt_ > 4) {
        state_ = 0;
        FindRoute(5);
        animation_cnt_ = 0;
        cnt_ = 0;
      }
      break;
  }
  return status_;
}

void CMover_Enemy_Azarashi::Render() const {
  if (state_ < 0) {
    CImageManager::GetIns()
        .Find("enemy_azarashi_intro")
        ->DrawRotaF(position_.x_, position_.y_, 0.0, 1.0,
                    Constant::kPriorityEnemy, (int)(animation_cnt_));
    return;
  }
  CImageManager::GetIns()
      .Find("enemy_azarashi")
      ->DrawRotaF(position_.x_, position_.y_, 0.0, 1.0,
                  Constant::kPriorityEnemy,
                  direction_ * 4 + (int)(animation_cnt_));
}

CMover_EnemyBase* CMover_Enemy_Azarashi::Clone(CVector position, int Level) {
  return new CMover_Enemy_Azarashi(position, Level);
}
