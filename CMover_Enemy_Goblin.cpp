#include "CMover_Enemy_Goblin.h"

#include "CEffect_Bright.h"
#include "CImageManager.h"
#include "CMover_Bullet_Axe.h"
#include "CNumberDrawer.h"
#include "CSoundManager.h"

CMover_Enemy_Goblin::CMover_Enemy_Goblin(CVector position, int Level)
    : CMover_EnemyBase(40, Level, 1.0, 1.5,
                       CAttribute(1.0).None(0.6).Fire(2.5).Thunder(0.8), 40,
                       0x00FF00, position, 2.5, 1.2, COF(0.8, 0.9, 0.03, 0.1)),
      test_dest_(0.0, 0.0),
      focus_(0.0) {}

int CMover_Enemy_Goblin::Update() {
  switch (state_) {
    case 0:
      if (cnt_ % 80 == 0) {
        FindRoute(6);
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
      animation_cnt_ += 0.2;
      if (animation_cnt_ > 4) animation_cnt_ = 0;
      break;
    case 1:
      if (cnt_ == 32) {
        med_->RegisterMover(std::make_shared<CMover_Bullet_Axe>(
            base_params_, position_, focus_, 6.0));
        CSoundManager::GetIns().Find("throw")->Play(CSound::PlayType::kBack);
      }
      if (cnt_ > 80) {
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
        FindRoute(6);
        animation_cnt_ = 0;
        cnt_ = 0;
      }
      break;
  }
  return status_;
}

void CMover_Enemy_Goblin::Render() const {
  if (state_ < 0) {
    CImageManager::GetIns()
        .Find("enemy_goblin_intro")
        ->DrawRota(position_, 0.0, 1.0, Constant::kPriorityEnemy,
                   (int)(animation_cnt_));
    return;
  }
  CImageManager::GetIns()
      .Find("enemy_goblin")
      ->DrawRota(position_, 0.0, 1.0, Constant::kPriorityEnemy,
                 direction_ * 4 + (int)(animation_cnt_));
  CEffect_Bright::GetIns().Register(
      CEffect_Bright::BrightDesc(position_, 192, 192));
}

CMover_EnemyBase* CMover_Enemy_Goblin::Clone(CVector position, int Level) {
  return new CMover_Enemy_Goblin(position, Level);
}
