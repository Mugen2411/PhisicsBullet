#include "CAnchor.h"

#include <float.h>

#include <algorithm>

#include "Constant.h"

CAnchor::CAnchor()
    : position_(0, 0),
      is_absolute_(false),
      scroll_limit_(DBL_MAX, DBL_MAX),
      diff_quake_(0, 0),
      engine_(seed_()),
      random_generator_(-1.0, 1.0) {
  std::srand(1);
}

void CAnchor::SetPosition(CVector newPos) {
  position_ = newPos;
  position_.x = fmax(0, position_.x);
  position_.y = fmax(0, position_.y);
  position_.x = fmin(scroll_limit_.x - Constant::kScreenW, position_.x);
  position_.y = fmin(scroll_limit_.y - Constant::kScreenH, position_.y);
}

void CAnchor::Update() {
  diff_quake_.x = 0;
  diff_quake_.y = 0;
  for (auto itr = quake_queue_.begin(); itr != quake_queue_.end();) {
    diff_quake_.x += random_generator_(engine_) * itr->power;
    diff_quake_.y += random_generator_(engine_) * itr->power;
    itr->power *= 0.98f;
    itr->duration--;
    if (itr->duration < 0) {
      itr = quake_queue_.erase(itr);
    } else {
      itr++;
    }
  }
}