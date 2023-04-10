#include <algorithm>
#include <iterator>

#include "CCoinParent.h"
#include "CMover_Player.h"

CCoinParent::CCoinParent(CGameMediator* m)
    : med_(m), mover_list_(), reserve_list_(), cnt(0) {}


void CCoinParent::Update() {
  int r = 0;
  for (auto itr = mover_list_.begin(); itr != mover_list_.end();) {
    (*itr)->BaseUpdate();
    r = (*itr)->Update();
    switch (r) {
      case CMover::Status::kAlive:
        med_->ApplyForceToMover(itr->get());
        (*itr)->CalcAcceleration();
        med_->HitToMover(itr->get());
        (*itr)->Move();
        break;
      case CMover::Status::kDead:
        (*itr)->Dead();
        itr = mover_list_.erase(itr);
        continue;
        break;
      case CMover::Status::kVanished:
        (*itr)->Disappear();
        itr = mover_list_.erase(itr);
        continue;
        break;
    }
    itr++;
  }
  if (reserve_list_.size() > 0) {
    std::copy(reserve_list_.begin(), reserve_list_.end(),
              std::back_inserter(mover_list_));
    reserve_list_.clear();
  }
  cnt++;
}

void CCoinParent::Render() {
  std::for_each(mover_list_.begin(), mover_list_.end(),
                [](std::shared_ptr<CMover> itr) {
                  if (itr->BaseRender()) itr->Render();
                });
#ifdef _DEBUG
  printfDx("Objects: %d\n", mover_list_.size());
#endif
}

void CCoinParent::Hit(std::shared_ptr<CMover> player) {
  for (std::shared_ptr<CMover> i : mover_list_) {
    if ((i->position_ - player->position_).GetLength2() <
        (i->GetSize() + player->GetSize()) *
            (i->GetSize() + player->GetSize())) {
      //i->HitDispatch(player);
      player->HitDispatch(i);
    }
  }
}