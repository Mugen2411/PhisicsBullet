#include "CCostume_Uniform.h"

#include "CMover_Shot_Uniform_Homing.h"
#include "CMover_Shot_Uniform_StrongMagic.h"
#include "CPower_Line.h"
#include "CSoundManager.h"

CCostume_Uniform::CCostume_Uniform(std::string gid_)
    : CCostumeBase(gid_) {
}

void CCostume_Uniform::WeakShot(CAttribute baseATK, CVector position,
                                float angle) {
  CSoundManager::GetIns().Find("little_magic")->Play(CSound::PlayType::kBack);
  RegisterShot(
      std::make_shared<CMover_Shot_Uniform_Homing>(baseATK, position, angle));
  player_ptr_->ResetCharge();
}

void CCostume_Uniform::ChargeShot(CAttribute baseATK, CVector position,
                                  float angle) {
  CSoundManager::GetIns().Find("middle_magic")->Play(CSound::PlayType::kBack);
  RegisterShot(std::make_shared<CMover_Shot_Uniform_StrongMagic>(
      baseATK, position, angle));
  player_ptr_->ResetCharge();
}
