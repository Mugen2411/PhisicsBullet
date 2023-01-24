#include "CCostume_Chinese.h"

#include "CMover_Shot_Chinese_Lantern.h"
#include "CPower_Line.h"
#include "CSoundManager.h"

CCostume_Chinese::CCostume_Chinese(std::string gid_)
    : CCostumeBase("media/graphic/character/komuk/costume/chinese/komuk.png",
                   0.1, 60, 1, 20, 4.5, 2.8, 25.0,
                   CAttribute(1.0).Aqua(2.0).Fire(0.4).Ice(0.4).Wind(3.0),
                   COF(0.7, 0.7, 0.1, 0.0), gid_) {
  detail_ = CTextDrawer::Text(
      "格闘には強そうなチャイナドレス。\nしかし格闘は一切しない。\n"
      "強射で複数の灯籠を浮かべ、\n連射の風で押し出す。\n"
      "灯籠は移動する速度が速いほど\n大きいダメージになる。",
      Constant::kCostumeDetailPosition, 0xFFFFFF, 0x000000, 0);
}

void CCostume_Chinese::WeakShot(CAttribute baseATK, CVector position,
                                float angle) {
  player_ptr_->RegisterPower(std::make_shared<CPower_Line>(
      position + CVector(angle) * 32, CVector(angle, 192.0), 64, 32,
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
