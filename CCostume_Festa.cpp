#include "CCostume_Festa.h"
#include "CMover_Shot_Festa_Superball.h"

CCostume_Festa::CCostume_Festa(CMover_Player* player)
	:CCostumeBase(player, "media/graphic/character/komuk/komuk.png", 0.1, 60, 12, 10, 2.5, 1.5, CAttribute(1.0).FLOWER(1.5))
{
}

void CCostume_Festa::WeakShot(double baseATK, CVector position, float angle)
{
}

void CCostume_Festa::ChargeShot(double baseATK, CVector position, float angle)
{
	for (int i = 0; i < 20; i++) {
		RegisterShot(std::make_shared<CMover_Shot_Festa_Superball>(baseATK, position, angle+(GetRand(160)/80.0 - 1.0)*Constant::PI/6));
	}
}
