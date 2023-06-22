#include "CCostume_Firefighter.h"

#include "Mover/Shot/FireFighter/CMover_Shot_Firefighter_Water.h"
#include "Power/CPower_Line.h"
#include "Sound/CSoundManager.h"

CCostume_Firefighter::CCostume_Firefighter(std::string gid_)
    : CCostumeBase(gid_) {
}

void CCostume_Firefighter::WeakShot(CAttribute baseATK, CVector position,
                                    float angle) {
  RegisterShot(std::make_shared<CMover_Shot_Firefigher_Water>(
      baseATK, position,
      angle + Constant::kPI / 20 * (GetRand(10) * 0.1 - 0.5)));
  player_ptr_->ApplyForce(CVector(angle+Constant::kPI) * 60.0);
  CSoundManager::GetIns().Find("splash")->Play(CSound::PlayType::kBack);
  player_ptr_->ReduceCharge(3.0);
}

void CCostume_Firefighter::ChargeShot(CAttribute baseATK, CVector position,
                                      float angle) {
  RegisterShot(std::make_shared<CMover_Shot_Firefigher_Water>(
      baseATK, position,
      angle + Constant::kPI / 24 * (GetRand(10) * 0.1 - 0.5)));
  player_ptr_->ReduceCharge(3.0);
}
