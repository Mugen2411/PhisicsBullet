#include "CCostume_Festa.h"

#include "CMover_Shot_Festa_Cork.h"
#include "CMover_Shot_Festa_Superball.h"
#include "CSoundManager.h"

CCostume_Festa::CCostume_Festa(std::string gid_)
    : CCostumeBase(gid_) {
}

void CCostume_Festa::WeakShot(CAttribute baseATK, CVector position,
                              float angle) {
  RegisterShot(
      std::make_shared<CMover_Shot_Festa_Cork>(baseATK, position, angle));
  CSoundManager::GetIns().Find("shot_cork")->Play(CSound::PlayType::kBack);
  player_ptr_->ResetCharge();
}

void CCostume_Festa::ChargeShot(CAttribute baseATK, CVector position,
                                float angle) {
  CSoundManager::GetIns().Find("throw")->Play(CSound::PlayType::kBack);
  for (int i = 0; i < 40; i++) {
    RegisterShot(std::make_shared<CMover_Shot_Festa_Superball>(
        baseATK, position,
        angle + (GetRand(160) / 80.0 - 1.0) * Constant::kPI / 4));
  }
  player_ptr_->ResetCharge();
}
