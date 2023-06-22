#include "CMover_Enemy_Yadokari.h"

#include "Graphic/Image/CImageManager.h"
#include "Mover/Bullet/CMover_Bullet_WaterSplash.h"
#include "Graphic/Draw/CNumberDrawer.h"
#include "Sound/CSoundManager.h"

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
      if (animCnt_.Get() > 3.5) {
        state_ = 0;
        FindRoute(5);
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
                   (int)(animCnt_.Get()));
    return;
  }
  CImageManager::GetIns()
      .Find("enemy_yadokari")
      ->DrawRota(position_, 0.0, 1.0, Constant::kPriorityEnemy,
                 direction_ * 4 + (int)(animCnt_.Get()));
}

CMover_EnemyBase* CMover_Enemy_Yadokari::Clone(CVector position, int Level) {
  return new CMover_Enemy_Yadokari(position, Level);
}
