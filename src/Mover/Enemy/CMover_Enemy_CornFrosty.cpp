#include "Data/CDataLoader.h"
#include "Graphic/Image/CImageManager.h"
#include "Mover/Bullet/CMover_Bullet_CornFrost.h"
#include "Mover/Enemy/CMover_Enemy_CornFrosty.h"
#include "Graphic/Draw/CNumberDrawer.h"
#include "Sound/CSoundManager.h"

CMover_Enemy_CornFrosty::CMover_Enemy_CornFrosty(CVector position, int Level)
    : CMover_EnemyBase("E_BudcornFrost", Level, position), test_dest_(0.0, 0.0) {}

int CMover_Enemy_CornFrosty::Update() {
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
        med_->RegisterMover(std::make_shared<CMover_Bullet_CornFrost>(
            base_params_, position_, (ppos - position_).GetAngle(), 4.0));
        CSoundManager::GetIns()
            .Find("pretty_throw")
            ->Play(CSound::PlayType::kBack);
        cnt_ = 0;
        state_ = 1;
        break;
      }
      cnt_++;
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
      break;
    case -1:
      if (animCnt_.Get() > 3.5) {
        state_ = 0;
        FindRoute(3);
        cnt_ = 0;
      }
      break;
  }
  return status_;
}

void CMover_Enemy_CornFrosty::Render() const {
  if (state_ < 0) {
    CImageManager::GetIns()
        .Find("enemy_bud_intro")
        ->DrawRotaF(position_.x_, position_.y_, 0.0, 1.0,
                    Constant::kPriorityEnemy, (int)(animCnt_.Get()));
    return;
  }
  CImageManager::GetIns()
      .Find("enemy_cornfrost")
      ->DrawRotaF(position_.x_, position_.y_, 0.0, 1.0,
                  Constant::kPriorityEnemy,
                  direction_ * 4 + (int)(animCnt_.Get()));
}

CMover_EnemyBase* CMover_Enemy_CornFrosty::Clone(CVector position, int Level) {
  return new CMover_Enemy_CornFrosty(position, Level);
}
