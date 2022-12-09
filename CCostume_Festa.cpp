#include "CCostume_Festa.h"
#include "CMover_Shot_Festa_Superball.h"
#include "CMover_Shot_Festa_Cork.h"
#include "CSoundManager.h"

CCostume_Festa::CCostume_Festa(std::string GID)
	:CCostumeBase("media/graphic/character/komuk/costume/festa/komuk.png", 0.1, 60, 12, 10, 3.0, 2.0, 20.0, CAttribute(0.9).FLOWER(1.5).AQUA(1.8), COF(0.5, 0.5, 0.05, 0.0), GID)
{
}

void CCostume_Festa::WeakShot(double baseATK, CVector position, float angle)
{
	RegisterShot(std::make_shared<CMover_Shot_Festa_Cork>(baseATK, position, angle));
	CSoundManager::getIns().find("shot_cork")->Play(CSound::PLAYTYPE::PT_BACK);
}

void CCostume_Festa::ChargeShot(double baseATK, CVector position, float angle)
{
	CSoundManager::getIns().find("throw")->Play(CSound::PLAYTYPE::PT_BACK);
	for (int i = 0; i < 20; i++) {
		RegisterShot(std::make_shared<CMover_Shot_Festa_Superball>(baseATK, position, angle+(GetRand(160)/80.0 - 1.0)*Constant::PI/4));
	}
}
