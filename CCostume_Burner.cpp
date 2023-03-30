#include "CCostume_Burner.h"
#include "CMover_Shot_Burner_Flame.h"
#include "CPower_Line.h"
#include "CSoundManager.h"

CCostume_Burner::CCostume_Burner(std::string gid_)
    : CCostumeBase(gid_) {}

void CCostume_Burner::WeakShot(CAttribute baseATK, CVector position,
                                    float angle) {
  RegisterShot(std::make_shared<CMover_Shot_Burner_Flame>(
      baseATK, position,
      angle + Constant::kPI / 20 * (GetRand(10) * 0.1 - 0.5)));
  player_ptr_->ApplyForce(CVector(angle + Constant::kPI) * 60.0);
  CSoundManager::GetIns().Find("little_fire")->Play(CSound::PlayType::kBack);
  player_ptr_->ReduceCharge(3.0);
}

void CCostume_Burner::ChargeShot(CAttribute baseATK, CVector position,
                                      float angle) {
  RegisterShot(std::make_shared<CMover_Shot_Burner_Flame>(
      baseATK, position,
      angle + Constant::kPI / 24 * (GetRand(10) * 0.1 - 0.5)));
  player_ptr_->ReduceCharge(3.0);
}
