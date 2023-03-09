#include "CCostume_Archer_Flame.h"

#include "CMover_Shot_Archer_FlameArrow.h"
#include "CMover_Shot_Archer_PlaneArrow.h"
#include "CSoundManager.h"

CCostume_Archer_Flame::CCostume_Archer_Flame(std::string gid_)
    : CCostumeBase(gid_) {
}

void CCostume_Archer_Flame::WeakShot(CAttribute baseATK, CVector position,
                                     float angle) {
  CSoundManager::GetIns().Find("throw")->Play(CSound::PlayType::kBack);
  RegisterShot(std::make_shared<CMover_Shot_Archer_PlaneArrow>(
      baseATK, position, angle));
}

void CCostume_Archer_Flame::ChargeShot(CAttribute baseATK, CVector position,
                                       float angle) {
  CSoundManager::GetIns().Find("throw")->Play(CSound::PlayType::kBack);
  CSoundManager::GetIns().Find("little_fire")->Play(CSound::PlayType::kBack);
  for (int i = -1; i < 2; i++) {
    RegisterShot(std::make_shared<CMover_Shot_Archer_FlameArrow>(
        baseATK, position, angle + i * Constant::kPI / 24));
  }
  player_ptr_->ResetCharge();
}
