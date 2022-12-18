#include "CCostume_Festa.h"
#include "CMover_Shot_Festa_Superball.h"
#include "CMover_Shot_Festa_Cork.h"
#include "CSoundManager.h"

CCostume_Festa::CCostume_Festa(std::string GID)
	:CCostumeBase("media/graphic/character/komuk/costume/festa/komuk.png", 0.1, 80, 12, 10, 3.0, 2.0, 20.0, CAttribute(0.9).FLOWER(1.5).AQUA(1.8), COF(0.5, 0.5, 0.05, 0.0), GID)
{
	detail = CTextDrawer::Text("縁日に着て行く浴衣。\nそもそも戦闘に向いていないので\n足が遅いが水の影響が少し少ない。\n連射は射的のコルク弾。\n扱いやすく連射が利く。\n強射はスーパーボール。\n広い範囲にたくさん投げるので狭い場所で有効。", Constant::Costume_detail_pos, 0xFFFFFF, 0x000000, 0);
}

void CCostume_Festa::WeakShot(double baseATK, CVector position, float angle)
{
	RegisterShot(std::make_shared<CMover_Shot_Festa_Cork>(baseATK, position, angle));
	CSoundManager::getIns().find("shot_cork")->Play(CSound::PLAYTYPE::PT_BACK);
}

void CCostume_Festa::ChargeShot(double baseATK, CVector position, float angle)
{
	CSoundManager::getIns().find("throw")->Play(CSound::PLAYTYPE::PT_BACK);
	for (int i = 0; i < 40; i++) {
		RegisterShot(std::make_shared<CMover_Shot_Festa_Superball>(baseATK, position, angle+(GetRand(160)/80.0 - 1.0)*Constant::PI/4));
	}
}
