#include "CAnchor.h"

#include <float.h>

#include <algorithm>

#include "Constant.h"

CAnchor::CAnchor()
    : position(0, 0),
      isAbsolute(false),
      ScrollLimit(DBL_MAX, DBL_MAX),
      diff_quake(0, 0),
      engine(seed()),
      randomGenerator(-1.0, 1.0) {
  std::srand(1);
}

void CAnchor::setPosition(CVector newPos) {
  position = newPos;
  position.x = fmax(0, position.x);
  position.y = fmax(0, position.y);
  position.x = fmin(ScrollLimit.x - Constant::ScreenW, position.x);
  position.y = fmin(ScrollLimit.y - Constant::ScreenH, position.y);
}

void CAnchor::Update() {
  diff_quake.x = 0;
  diff_quake.y = 0;
  for (auto itr = quakeQueue.begin(); itr != quakeQueue.end();) {
    diff_quake.x += randomGenerator(engine) * itr->power;
    diff_quake.y += randomGenerator(engine) * itr->power;
    itr->power *= 0.98f;
    itr->duration--;
    if (itr->duration < 0) {
      itr = quakeQueue.erase(itr);
    } else {
      itr++;
    }
  }
}