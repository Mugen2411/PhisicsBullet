#include "CCostume_Festa.h"

#include "CMover_Shot_Festa_Cork.h"
#include "CMover_Shot_Festa_Superball.h"
#include "CSoundManager.h"

CCostume_Festa::CCostume_Festa(std::string gid_)
    : CCostumeBase("media/graphic/character/komuk/costume/festa/komuk.png", 0.1,
                   80, 12, 10, 3.0, 2.0, 20.0,
                   CAttribute(0.9).Flower(1.5).Aqua(1.32),
                   COF(0.5, 0.5, 0.05, 0.0), gid_) {
  detail_ = CTextDrawer::Text(
      "縁日に着て行く浴衣。\nそもそも戦闘に向いていないので\n足が遅いが水の影響"
      "が少し少ない。\n連射は射的のコルク弾。\n扱いやすく連射が利く。\n強射はス"
      "ーパーボール。\n広い範囲にたくさん投げるので狭い場所で有効。",
      Constant::kCostumeDetailPosition, 0xFFFFFF, 0x000000, 0);
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
