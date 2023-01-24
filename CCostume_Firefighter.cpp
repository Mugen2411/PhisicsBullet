#include "CCostume_Firefighter.h"

#include "CMover_Shot_Firefighter_Water.h"
#include "CMover_Shot_Uniform_StrongMagic.h"
#include "CPower_Line.h"
#include "CSoundManager.h"

CCostume_Firefighter::CCostume_Firefighter(std::string gid_)
    : CCostumeBase(
          "media/graphic/character/komuk/costume/firefighter/komuk.png", 0.1,
          120, 2, 2, 2.2, 1.5, 30.0,
          CAttribute(1.0).Fire(3.0).Wind(0.5).Thunder(0.7),
          COF(0.8, 0.96, 0.05, 0.0), gid_) {
  detail_ = CTextDrawer::Text(
      "耐火性に優れた消防士の制服。\nチャージした時間だけ連射することが出来る。\n水属性が弱点の敵に大ダメージだ。",
      Constant::kCostumeDetailPosition, 0xFFFFFF, 0x000000, 0);
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
