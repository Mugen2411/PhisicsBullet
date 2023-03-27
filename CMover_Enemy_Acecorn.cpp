#include "CMover_Enemy_Acecorn.h"

#include "CImageManager.h"
#include "CMover_Bullet_Corn.h"
#include "CNumberDrawer.h"
#include "CSoundManager.h"

CMover_Enemy_Acecorn::CMover_Enemy_Acecorn(CVector position, int Level)
    : CMover_EnemyBase("E_Acecorn", Level, position),
      test_dest_(0.0, 0.0),
      focus_(0.0) {}

int CMover_Enemy_Acecorn::Update() {
  switch (state_) {
    case 0:
      if (cnt_ % 60 == 0) {
        if (GetRand(5) == 0) {
          cnt_ = 0;
          FindTargetByDistance(6);
          state_ = 2;
          return status_;
        } else
          FindRoute(3);
      }
      if (!route_.empty()) {
        Move_on_Route();
      } else {
        CVector ppos = med_->GetPlayerPosition();
        focus_ = (ppos - position_).GetAngle();
        cnt_ = 0;
        state_ = 1;
        break;
      }
      cnt_++;
      animation_cnt_ += 0.3;
      if (animation_cnt_ > 4) animation_cnt_ = 0;
      break;
    case 1:
      if (cnt_ == 10) {
        med_->RegisterMover(std::make_shared<CMover_Bullet_Corn>(
            base_params_, position_, focus_, 6.0));
        CSoundManager::GetIns()
            .Find("pretty_throw")
            ->Play(CSound::PlayType::kBack);
      }
      if (cnt_ > 20) {
        state_ = 0;
        cnt_ = 0;
        break;
      }
      animation_cnt_ += 0.3;
      if (animation_cnt_ > 4) animation_cnt_ = 0;
      cnt_++;
      break;
    case 2:
      if (!route_.empty()) {
        Move_on_Route();
      } else {
        CVector ppos = med_->GetPlayerPosition();
        focus_ = (ppos - position_).GetAngle();
        for (int i = 0; i < 12; i++) {
          med_->RegisterMover(std::make_shared<CMover_Bullet_Corn>(
              base_params_, position_, focus_ + Constant::kPI2 / 12 * i, 6.5));
        }
        cnt_ = 0;
        state_ = 0;
      }
      cnt_++;
      break;
    case -1:
      animation_cnt_ += 0.1;
      if (animation_cnt_ > 4) {
        state_ = 0;
        FindRoute(3);
        animation_cnt_ = 0;
        cnt_ = 0;
      }
      break;
  }
  return status_;
}

void CMover_Enemy_Acecorn::Render() const {
  if (state_ < 0) {
    CImageManager::GetIns()
        .Find("enemy_bud_intro")
        ->DrawRotaF(position_.x_, position_.y_, 0.0, 1.0, Constant::kPriorityEnemy,
                   (int)(animation_cnt_));
    return;
  }
  CImageManager::GetIns()
      .Find("enemy_acecorn")
      ->DrawRotaF(position_.x_, position_.y_, 0.0, 1.0, Constant::kPriorityEnemy,
                 direction_ * 4 + (int)(animation_cnt_));
}

CMover_EnemyBase* CMover_Enemy_Acecorn::Clone(CVector position, int Level) {
  return new CMover_Enemy_Acecorn(position, Level);
}
