#include "CCostume_Swimsuit.h"

#include "Effect/CEffectParent.h"
#include "Effect/CEffect_Bat_Swing.h"
#include "Mover/Shot/Swimsuit/CMover_Shot_Swimsuit_Bat.h"
#include "Mover/Shot/Swimsuit/CMover_Shot_Swimsuit_iPhone.h"
#include "Sound/CSoundManager.h"

CCostume_Swimsuit::CCostume_Swimsuit(std::string gid_)
    : CCostumeBase(gid_) {
}

void CCostume_Swimsuit::WeakShot(CAttribute baseATK, CVector position,
                                 float angle) {
  CSoundManager::GetIns().Find("throw")->Play(CSound::PlayType::kBack);
  player_ptr_->RegisterShot(
      std::make_shared<CMover_Shot_Swimsuit_iPhone>(baseATK, position, angle));
  player_ptr_->ResetCharge();
}

void CCostume_Swimsuit::ChargeShot(CAttribute baseATK, CVector position,
                                   float angle) {
  CSoundManager::GetIns().Find("bat_swing")->Play(CSound::PlayType::kBack);
  for (int i = 0; i < 8; i++) {
    player_ptr_->RegisterShot(std::make_shared<CMover_Shot_Swimsuit_Bat>(
        baseATK, position, angle, i * 2));
  }
  player_ptr_->ResetCharge();
  CEffectParent::RegisterEffect(
      std::make_shared<CEffect_Bat_Swing>(position, angle));
}