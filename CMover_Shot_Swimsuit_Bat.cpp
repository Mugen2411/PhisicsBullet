#include "CMover_Shot_Swimsuit_Bat.h"

#include "CImageManager.h"

CMover_Shot_Swimsuit_Bat::CMover_Shot_Swimsuit_Bat(CAttribute baseATK,
                                                   CVector position,
                                                   double angle, double speed)
    : CMover_ShotBase(baseATK, CAttribute(0.0).None(90), position, 24,
                      CVector(angle) * speed, 64.0, COF(0.00, 0.0, 0.00, 0.0),
                      0x7F7F00),
      cnt_(0) {}

int CMover_Shot_Swimsuit_Bat::Update() {
  if (cnt_ > 9) SetStatus(Status::kDead);
  cnt_++;
  return status_;
}

void CMover_Shot_Swimsuit_Bat::Render() const {}
