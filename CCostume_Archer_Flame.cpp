#include "CCostume_Archer_Flame.h"
#include "CMover_Shot_Archer_PlaneArrow.h"
#include "CMover_Shot_Archer_FlameArrow.h"

CCostume_Archer_Flame::CCostume_Archer_Flame(std::string GID) :
	CCostumeBase("media/graphic/character/komuk/costume/archer/flame.png", 0.15, 40, 24, 10, 4.0, 2.0, 18.0, CAttribute(1.0).FIRE(1.5), COF(0.7, 0.97, 0.05, 0.0), GID) {
}

void CCostume_Archer_Flame::WeakShot(double baseATK, CVector position, float angle)
{
	RegisterShot(std::make_shared<CMover_Shot_Archer_PlaneArrow>(baseATK, position, angle));
}

void CCostume_Archer_Flame::ChargeShot(double baseATK, CVector position, float angle)
{
	for (int i = -1; i < 2; i++) {
		RegisterShot(std::make_shared<CMover_Shot_Archer_FlameArrow>(baseATK, position, angle+i*Constant::PI/24));
	}
}
