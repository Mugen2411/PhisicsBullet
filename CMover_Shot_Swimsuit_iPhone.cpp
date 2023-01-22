#include "CMover_Shot_Swimsuit_iPhone.h"

#include "CEffectParent.h"
#include "CEffect_BulletDelete.h"
#include "CImageManager.h"
#include "CSoundManager.h"

CMover_Shot_Swimsuit_iPhone::CMover_Shot_Swimsuit_iPhone(CAttribute baseATK,
                                                         CVector position,
                                                         float angle)
    : CMover_ShotBase(baseATK, CAttribute(0.0).None(10).Thunder(50), position,
                      24, CVector(angle) * 16.0, 2.0,
                      COF(0.02, 0.05, 0.05, 0.1), 0x7F7F7F),
      render_angle_(0.0f) {}

void CMover_Shot_Swimsuit_iPhone::Dead() {
  CEffectParent::RegisterEffect(std::make_shared<CEffect_BulletDelete>(
      position_, velocity_, size_, effect_color_));
  CSoundManager::GetIns().Find("glassBreak")->Play(CSound::PlayType::kBack);
}

int CMover_Shot_Swimsuit_iPhone::Update() {
  if (velocity_.GetLength2() < 0.05) {
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
