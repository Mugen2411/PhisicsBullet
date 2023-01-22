#include "CCostume_Uniform.h"

#include "CMover_Shot_Uniform_Homing.h"
#include "CMover_Shot_Uniform_StrongMagic.h"
#include "CPower_Line.h"
#include "CSoundManager.h"

CCostume_Uniform::CCostume_Uniform(std::string gid_)
    : CCostumeBase("media/graphic/character/komuk/costume/uniform/komuk.png",
                   0.1, 60, 12, 20, 3.5, 1.8, 20.0, CAttribute(1.0).Aqua(0.98),
                   COF(0.7, 0.96, 0.05, 0.0), gid_) {
  detail_ = CTextDrawer::Text(
      "最初に来ていた制服。最も基本的な衣装であり、\n全ての耐性が平均的。\n連射"
      "は誘導魔法弾。\n最も近い敵を探して攻撃する。\nしかし壁に当たると消えてし"
      "まう。\n強射は高出力魔法弾。\n周囲の環境の影響を受けずに\nまっすぐ飛んで"
      "高めのダメージを与える。",
      Constant::kCostumeDetailPosition, 0xFFFFFF, 0x000000, 0);
}

void CCostume_Uniform::WeakShot(CAttribute baseATK, CVector position_,
                                float angle) {
  CSoundManager::GetIns().Find("little_magic")->Play(CSound::PlayType::kBack);
  RegisterShot(
      std::make_shared<CMover_Shot_Uniform_Homing>(baseATK, position_, angle));
  // p_player->RegisterPower(std::make_shared<CPower_Line>(position_ +
  // CVector(angle_) * 32, CVector(angle_, 128.0), 64, 30, 1));
}

void CCostume_Uniform::ChargeShot(CAttribute baseATK, CVector position_,
                                  float angle) {
  CSoundManager::GetIns().Find("middle_magic")->Play(CSound::PlayType::kBack);
  RegisterShot(std::make_shared<CMover_Shot_Uniform_StrongMagic>(
      baseATK, position_, angle));
}
