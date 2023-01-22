#include "CMoverParent.h"

#include <algorithm>
#include <iterator>

#include "CMover_Player.h"

CMoverParent::CMoverParent(CGameMediator* m)
    : med_(m), mover_list_(), reserve_list_(), cnt(0) {}

std::weak_ptr<CMover> CMoverParent::GetMover(int ID, int num) {
  int i = 0;
  for (std::shared_ptr<CMover> v : mover_list_) {
    if (v->category_ == ID) {
      if (i == num) return v;
      i++;
    }
  }
  return std::weak_ptr<CMover>();
}

int CMoverParent::GetCountByCategory(int ID) {
  int r = 0;
  for (auto& i : mover_list_) {
    if (i->category_ == ID) r++;
  }
  return r;
}

void CMoverParent::Update() {
  Hit();
  int r = 0;
  for (auto itr = mover_list_.begin(); itr != mover_list_.end();) {
    (*itr)->BaseUpdate();
    r = (*itr)->Update();
    med_->ApplyForceToMover(itr->get());
    med_->HitToMover(itr->get());
    (*itr)->Move();
    switch (r) {
      case CMover::Status::kAlive:
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

void CMoverParent::Render() {
  std::for_each(mover_list_.begin(), mover_list_.end(),
                [](std::shared_ptr<CMover> itr) {
                  if (itr->BaseRender()) itr->Render();
                });
#ifdef _DEBUG
  printfDx("Objects: %d\n", mover_list_.size());
#endif
}

void CMoverParent::Hit() {
  for (std::shared_ptr<CMover> i : mover_list_) {
    for (std::shared_ptr<CMover> j : mover_list_) {
      if (i == j) continue;
      if ((i->position_ - j->position_).GetLength2() <
          (i->GetSize() + j->GetSize()) * (i->GetSize() + j->GetSize())) {
        i->HitDispatch(j);
      }
    }
  }
}
