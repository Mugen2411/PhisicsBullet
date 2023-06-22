#include "CCostume_Chinese.h"

#include "Mover/Shot/Chinese/CMover_Shot_Chinese_Lantern.h"
#include "Power/CPower_Line.h"
#include "Sound/CSoundManager.h"

CCostume_Chinese::CCostume_Chinese(std::string gid_)
    : CCostumeBase(gid_) {
}

void CCostume_Chinese::WeakShot(CAttribute baseATK, CVector position,
                                float angle) {
  player_ptr_->RegisterPower(std::make_shared<CPower_Line>(
      position + CVector(angle) * 16, CVector(angle, 192.0), 48, 8,
      CAttribute(0.0).Wind(2.0) * baseATK, 1));
  player_ptr_->ResetCharge();
}

void CCostume_Chinese::ChargeShot(CAttribute baseATK, CVector position,
                                  float angle) {
  CSoundManager::GetIns().Find("little_fire")->Play(CSound::PlayType::kBack);
  for (int i = 0; i < 5; i++) {
    RegisterShot(std::make_shared<CMover_Shot_Chinese_Lantern>(
        baseATK, position, angle));
  }
  player_ptr_->ResetCharge();
}
