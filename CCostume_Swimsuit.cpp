#include "CCostume_Swimsuit.h"
#include "CSoundManager.h"
#include "CMover_Shot_Swimsuit_iPhone.h"
#include "CMover_Shot_Swimsuit_Bat.h"
#include "CEffectParent.h"
#include "CEffect_Bat_Swing.h"

CCostume_Swimsuit::CCostume_Swimsuit(std::string GID)
	:CCostumeBase("media/graphic/character/komuk/costume/swimsuit/komuk.png", 0.1, 60, 24, 30, 4.0, 2.0, 18.0, CAttribute(0.9).AQUA(3.5).FIRE(0.7).THUNDER(0.5), COF(0.6, 0.1, 0.05, 0.0), GID)
{
	detail = CTextDrawer::Text("誰かさんの趣味で作られたスクール水着。\nどう見ても戦闘には適していないが\n高い水耐性を誇る。\n連射は型落ちのiPh〇ne。\n雷属性のダメージを含む。\n強射は棍棒。スイカの代わりに敵の頭をカチ割る。", Constant::Costume_detail_pos, 0xFFFFFF, 0x000000, 0);
}

void CCostume_Swimsuit::WeakShot(double baseATK, CVector position, float angle)
{
	CSoundManager::getIns().find("throw")->Play(CSound::PLAYTYPE::PT_BACK);
	p_player->RegisterShot(std::make_shared<CMover_Shot_Swimsuit_iPhone>(baseATK, position, angle));
}

void CCostume_Swimsuit::ChargeShot(double baseATK, CVector position, float angle)
{
	CSoundManager::getIns().find("bat_swing")->Play(CSound::PLAYTYPE::PT_BACK);
	for (int i = 0; i < 8; i++) {
		p_player->RegisterShot(std::make_shared<CMover_Shot_Swimsuit_Bat>(baseATK, position, angle, i*2));
	}
	CEffectParent::RegisterEffect(std::make_shared<CEffect_Bat_Swing>(position, angle));
}