#include "CMover_Mother_Static.h"

#include "CImageManager.h"

CMover_Mother_Static::CMover_Mother_Static(CVector position, int Level,
                                           std::vector<MotherDesc> md,
                                           int wait_time)
    : CMover_EnemyBase("M_Static", Level, position),
      descList_(md),
      stateList_(md.size()),
      cnt_(0),
      wait_time_(wait_time) {}

int CMover_Mother_Static::Update() {
  switch (state_) {
    case 0:
      if (cnt_ > wait_time_) {
        state_ = 1;
        cnt_ = 0;
        ResetState();
      }
      break;
    case 1:
      if (cnt_ == 10) {
        bool droped = false;
        for (int i = 0; i < descList_.size(); i++) {
          if (stateList_[i].amount > descList_[i].amount) continue;
          stateList_[i].amount++;
          med_->RegisterMover(CEF_.Create(
              descList_[i].gid, position_ + CVector(Constant::kPI2 * GetRand(64) / 64.0) * 32.0,
              base_params_.level_));
          droped |= true;
        }
        if (!droped) {
          state_ = 0;
          cnt_ = 0;
        }
        cnt_ = 0;
      }
      break;
    case -1:
      state_ = 1;
      break;
  }
  cnt_++;
  acceleration_ = CVector(0.0, 0.0);
  return status_;
}

void CMover_Mother_Static::ResetState() {
  for (auto& i : stateList_) {
    i.amount = 0;
  }
}

void CMover_Mother_Static::Render() const {
  CImageManager::GetIns()
      .Find("mother_hole")
      ->DrawRota(position_, 0.0f, 1.0f, Constant::kPriorityEnemy);
}

CMover_EnemyBase* CMover_Mother_Static::Clone(CVector position, int Level) {
  return new CMover_Mother_Static(position, Level, descList_, wait_time_);
}