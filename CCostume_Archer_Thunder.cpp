#include "CCostume_Archer_Thunder.h"
#include "CMover_Shot_Archer_ThunderArrow.h"
#include "CMover_Shot_Archer_PlaneArrow.h"
#include "CSoundManager.h"

CCostume_Archer_Thunder::CCostume_Archer_Thunder(std::string gid_)
    : CCostumeBase(gid_) {}

void CCostume_Archer_Thunder::WeakShot(CAttribute baseATK, CVector position,
                                     float angle) {
  CSoundManager::GetIns().Find("throw")->Play(CSound::PlayType::kBack);
  RegisterShot(std::make_shared<CMover_Shot_Archer_PlaneArrow>(
      baseATK, position, angle));
}

void CCostume_Archer_Thunder::ChargeShot(CAttribute baseATK, CVector position,
                                       float angle) {
  CSoundManager::GetIns().Find("throw")->Play(CSound::PlayType::kBack);
  CSoundManager::GetIns().Find("little_fire")->Play(CSound::PlayType::kBack);
  for (int i = -1; i < 2; i++) {
    RegisterShot(std::make_shared<CMover_Shot_Archer_ThunderArrow>(
        baseATK, position, angle + i * Constant::kPI / 24));
  }
  player_ptr_->ResetCharge();
}
