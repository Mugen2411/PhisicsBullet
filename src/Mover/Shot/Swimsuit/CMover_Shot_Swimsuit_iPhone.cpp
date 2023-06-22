#include "CMover_Shot_Swimsuit_iPhone.h"

#include "Effect/CEffectParent.h"
#include "Effect/CEffect_BulletDelete.h"
#include "Graphic/Image/CImageManager.h"
#include "Sound/CSoundManager.h"

CMover_Shot_Swimsuit_iPhone::CMover_Shot_Swimsuit_iPhone(CAttribute baseATK,
                                                         CVector position,
                                                         float angle)
    : CMover_ShotBase("S_Swimsuit_iPhone", baseATK, position, CVector(angle) * 20.0),
      render_angle_(0.0f) {}

void CMover_Shot_Swimsuit_iPhone::Dead() {
  CEffectParent::RegisterEffect(std::make_shared<CEffect_BulletDelete>(
      position_, velocity_, size_, effect_color_));
  CSoundManager::GetIns().Find("glassBreak")->Play(CSound::PlayType::kBack);
}

int CMover_Shot_Swimsuit_iPhone::Update() {
  if (velocity_.GetLength() < Constant::kDynamicBorder) {
    SetStatus(Status::kDead);
  }
  render_angle_ += (float)(Constant::kPI2 * Constant::kPerFrame * 1.5);
  return status_;
}

void CMover_Shot_Swimsuit_iPhone::Render() const {
  CImageManager::GetIns()
      .Find("shot_swimsuit_iphone")
      ->DrawRota(position_, velocity_.GetAngle() + render_angle_, 1,
                 Constant::kPriorityShot);
}
