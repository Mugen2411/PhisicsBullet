#include "CCostume_Uniform.h"
#include "CMover_Shot_Uniform_Homing.h"
#include "CMover_Shot_Uniform_StrongMagic.h"

CCostume_Uniform::CCostume_Uniform(std::string GID) :
	CCostumeBase("media/graphic/character/komuk/costume/uniform/komuk.png", 0.1, 60, 12, 20, 3.0, 2.0, 60.0,CAttribute(1.0), COF(0.5, 0.2, 0.1, 0.0),GID) {
}

void CCostume_Uniform::WeakShot(double baseATK, CVector position, float angle)
{
	RegisterShot(std::make_shared<CMover_Shot_Uniform_Homing>(baseATK, position, angle));
}

void CCostume_Uniform::ChargeShot(double baseATK, CVector position, float angle)
{
	RegisterShot(std::make_shared<CMover_Shot_Uniform_StrongMagic>(baseATK, position, angle));
}
