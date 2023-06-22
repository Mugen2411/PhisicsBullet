#include "CEffect_Bat_Swing.h"

#include "Graphic/Image/CImageManager.h"

CEffect_Bat_Swing::CEffect_Bat_Swing(CVector position_, float angle)
    : CEffect(position_), angle_(angle), cnt_(0) {}

void CEffect_Bat_Swing::Update() {
  cnt_++;
  if (cnt_ > 16) status_ = 1;
}

void CEffect_Bat_Swing::Render() const {
  CImageManager::GetIns()
      .Find("effect_bat")
      ->DrawRota(position_ + CVector(min(cnt_, 8) * 8 * cos(angle_),
                                    min(cnt_, 8) * 8 * sin(angle_)),
                 angle_, min(cnt_, 8) / 8.0f, Constant::kPriorityShot);
  if (cnt_ <= 8)
    CImageManager::GetIns()
        .Find("effect_bathead")
        ->DrawRota(position_ + CVector(min(cnt_, 8) * 16 * cos(angle_),
                                       min(cnt_, 8) * 16 * sin(angle_)),
                    angle_,
                    2.0f - min(cnt_, 8) / 8.0f, Constant::kPriorityShot + 1);
}
