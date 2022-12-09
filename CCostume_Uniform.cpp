#include "CCostume_Uniform.h"
#include "CMover_Shot_Uniform_Homing.h"
#include "CMover_Shot_Uniform_StrongMagic.h"
#include "CSoundManager.h"

CCostume_Uniform::CCostume_Uniform(std::string GID) :
	CCostumeBase("media/graphic/character/komuk/costume/uniform/komuk.png", 0.1, 60, 12, 20, 3.5, 1.8, 20.0,
		CAttribute(1.0), COF(0.7, 0.96, 0.05, 0.0),GID) {
	detail = CTextDrawer::Text("最初に来ていた制服。最も基本的な衣装であり、\n全ての耐性が平均的。\n連射は誘導魔法弾。\n最も近い敵を探して攻撃する。\nしかし壁に当たると消えてしまう。\n強射は高出力魔法弾。\n周囲の環境の影響を受けずに\nまっすぐ飛んで高めのダメージを与える。", Constant::Costume_detail_pos, 0xFFFFFF, 0x000000, 0);
}

void CCostume_Uniform::WeakShot(double baseATK, CVector position, float angle)
{
	CSoundManager::getIns().find("little_magic")->Play(CSound::PLAYTYPE::PT_BACK);
	RegisterShot(std::make_shared<CMover_Shot_Uniform_Homing>(baseATK, position, angle));
}

void CCostume_Uniform::ChargeShot(double baseATK, CVector position, float angle)
{
	CSoundManager::getIns().find("middle_magic")->Play(CSound::PLAYTYPE::PT_BACK);
	RegisterShot(std::make_shared<CMover_Shot_Uniform_StrongMagic>(baseATK, position, angle));
}
