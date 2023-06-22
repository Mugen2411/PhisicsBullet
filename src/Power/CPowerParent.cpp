#include "CPowerParent.h"

#include "CPower.h"
#include "CPower_Line.h"

CPowerParent::CPowerParent(CGameMediator* m) : med_(m) {}

void CPowerParent::Add(const std::shared_ptr<CPower>& p) {
  p->SetParent(this);
  power_list_.push_back(p);
}

void CPowerParent::ApplyForceToMover(CMover* m) {
  for (auto itr = power_list_.begin(); itr != power_list_.end(); itr++) {
    (*itr)->ApplyForceToMover(m);
  }
}

void CPowerParent::Update() {
  int r = 0;
  for (auto itr = power_list_.begin(); itr != power_list_.end();) {
    r = (*itr)->Update();
    switch (r) {
      case 0:
        break;
      case 1:
        itr = power_list_.erase(itr);
        continue;
        break;
    }
    itr++;
  }
}

void CPowerParent::Render() {
  for (auto itr = power_list_.begin(); itr != power_list_.end(); itr++) {
    (*itr)->Render();
  }
}
