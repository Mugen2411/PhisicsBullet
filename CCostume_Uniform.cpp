#include "CCostume_Uniform.h"
#include "CMover_Shot_Uniform_Homing.h"
#include "CMover_Shot_Uniform_StrongMagic.h"

CCostume_Uniform::CCostume_Uniform(CMover_Player* player) :
	CCostumeBase(player ,"media/graphic/character/komuk/komuk.png", 0.1, 60, 20, 20, 3.0, 24.0, CAttribute(1.0)) {
}

std::shared_ptr<CMover_ShotBase> CCostume_Uniform::WeakShot(double baseATK, CVector position, float angle)
{
	return std::make_shared<CMover_Shot_Uniform_Homing>(baseATK, position, angle);
}

std::shared_ptr<CMover_ShotBase> CCostume_Uniform::ChargeShot(double baseATK, CVector position, float angle)
{
	return std::make_shared<CMover_Shot_Uniform_StrongMagic>(baseATK, position, angle);
}
