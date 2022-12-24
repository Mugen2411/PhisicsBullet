#include "CCostume_Archer_Flame.h"
#include "CMover_Shot_Archer_PlaneArrow.h"
#include "CMover_Shot_Archer_FlameArrow.h"
#include "CSoundManager.h"

CCostume_Archer_Flame::CCostume_Archer_Flame(std::string GID) :
	CCostumeBase("media/graphic/character/komuk/costume/archer/flame.png", 0.15, 40, 24, 10, 4.0, 2.0, 18.0,
		CAttribute(1.0).FIRE(1.5).AQUA(0.6), COF(0.7, 0.97, 0.05, 0.0), GID) {
	detail = CTextDrawer::Text("火属性の弓を操るアーチャー衣装。\n戦闘に適しており足が速いが水にめっぽう弱い。\n連射は普通の弓。扱いやすい。\n強射は火属性を纏った弓を3つ放つ。\n火力がとても高い。", Constant::Costume_detail_pos, 0xFFFFFF, 0x000000, 0);
}

void CCostume_Archer_Flame::WeakShot(CAttribute baseATK, CVector position, float angle)
{
	CSoundManager::getIns().find("throw")->Play(CSound::PLAYTYPE::PT_BACK);
	RegisterShot(std::make_shared<CMover_Shot_Archer_PlaneArrow>(baseATK, position, angle));
}

void CCostume_Archer_Flame::ChargeShot(CAttribute baseATK, CVector position, float angle)
{
	CSoundManager::getIns().find("throw")->Play(CSound::PLAYTYPE::PT_BACK);
	CSoundManager::getIns().find("little_fire")->Play(CSound::PLAYTYPE::PT_BACK);
	for (int i = -1; i < 2; i++) {
		RegisterShot(std::make_shared<CMover_Shot_Archer_FlameArrow>(baseATK, position, angle+i*Constant::PI/24));
	}
}
