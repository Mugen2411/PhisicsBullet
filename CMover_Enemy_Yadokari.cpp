#include "CMover_Enemy_Yadokari.h"

#include "CImageManager.h"
#include "CMover_Bullet_WaterSplash.h"
#include "CNumberDrawer.h"
#include "CSoundManager.h"

CMover_Enemy_Yadokari::CMover_Enemy_Yadokari(CVector position, int Level)
    : CMover_EnemyBase("E_Yadokari", Level, position),
      test_dest_(0.0, 0.0),
      focus_(0.0) {}

int CMover_Enemy_Yadokari::Update() {
  switch (state_) {
    case 0:
      if (cnt_ % 60 == 0) {
        FindRoute(5);
      }
      if (!route_.empty())
        Move_on_Route();
      else {
        CVector ppos = med_->GetPlayerPosition();
        focus_ = (ppos - position_).GetAngle();
        state_ = 1;
        cnt_ = 0;
        break;
      }
      cnt_++;
      animation_cnt_ += 0.3;
      if (animation_cnt_ > 4) animation_cnt_ = 0;
      break;
    case 1:
      if (cnt_ == 25) {
        for (int i = 0; i < 3; i++) {
          med_->RegisterMover(std::make_shared<CMover_Bullet_WaterSplash>(
              base_params_, position_, focus_, 3.2 + i * 1.8));
        }
        CSoundManager::GetIns().Find("splash")->Play(CSound::PlayType::kBack);
      }
      if (cnt_ > 60) {
        state_ = 0;
        cnt_ = 0;
        break;
      }
      cnt_++;
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

void CMover_Enemy_Yadokari::Render() const {
  if (state_ < 0) {
    CImageManager::GetIns()
        .Find("enemy_yadokari_intro")
        ->DrawRota(position_, 0.0, 1.0, Constant::kPriorityEnemy,
                   (int)(animation_cnt_));
    return;
  }
  CImageManager::GetIns()
      .Find("enemy_yadokari")
      ->DrawRota(position_, 0.0, 1.0, Constant::kPriorityEnemy,
                 direction_ * 4 + (int)(animation_cnt_));
}

CMover_EnemyBase* CMover_Enemy_Yadokari::Clone(CVector position, int Level) {
  return new CMover_Enemy_Yadokari(position, Level);
}
