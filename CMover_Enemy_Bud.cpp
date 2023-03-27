#include "CMover_Enemy_Bud.h"

#include "CImageManager.h"
#include "CMover_Bullet_Corn.h"
#include "CNumberDrawer.h"
#include "CSoundManager.h"
#include "CDataLoader.h"

CMover_Enemy_Bud::CMover_Enemy_Bud(CVector position, int Level)
    : CMover_EnemyBase("E_Budcorn", Level, position),
      test_dest_(0.0, 0.0) {
}

int CMover_Enemy_Bud::Update() {
  switch (state_) {
    case 0:
      if (cnt_ % 60 == 0) {
        if (GetRand(5) == 0) {
          FindTargetByDistance(6);
          state_ = 2;
          cnt_ = 0;
        } else
          FindRoute(3);
      }
      if (!route_.empty()) {
        Move_on_Route();
      } else {
        CVector ppos = med_->GetPlayerPosition();
        med_->RegisterMover(std::make_shared<CMover_Bullet_Corn>(
            base_params_, position_, (ppos - position_).GetAngle(), 4.0));
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
      if (cnt_ > 30) {
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
        FindTargetByDistance(4);
      cnt_++;
      animation_cnt_ += 0.3;
      if (animation_cnt_ > 4) animation_cnt_ = 0;
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

void CMover_Enemy_Bud::Render() const {
  if (state_ < 0) {
    CImageManager::GetIns()
        .Find("enemy_bud_intro")
        ->DrawRotaF(position_.x_, position_.y_, 0.0, 1.0, Constant::kPriorityEnemy,
                   (int)(animation_cnt_));
    return;
  }
  CImageManager::GetIns()
      .Find("enemy_bud")
      ->DrawRotaF(position_.x_, position_.y_, 0.0, 1.0, Constant::kPriorityEnemy,
                 direction_ * 4 + (int)(animation_cnt_));
}

CMover_EnemyBase* CMover_Enemy_Bud::Clone(CVector position, int Level) {
  return new CMover_Enemy_Bud(position, Level);
}
