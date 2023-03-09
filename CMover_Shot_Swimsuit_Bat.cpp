#include "CMover_Shot_Swimsuit_Bat.h"

#include "CImageManager.h"

CMover_Shot_Swimsuit_Bat::CMover_Shot_Swimsuit_Bat(CAttribute baseATK,
                                                   CVector position,
                                                   double angle, double speed)
    : CMover_ShotBase("S_Swimsuit_Bat", baseATK, position, CVector(angle) * speed),
      cnt_(0) {}

int CMover_Shot_Swimsuit_Bat::Update() {
  if (cnt_ > 9) SetStatus(Status::kDead);
  cnt_++;
  return status_;
}

void CMover_Shot_Swimsuit_Bat::Render() const {}
