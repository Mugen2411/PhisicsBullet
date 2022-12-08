#include "CMover_Shot_Uniform_Homing.h"
#include "CImageManager.h"

CMover_Shot_Uniform_Homing::CMover_Shot_Uniform_Homing(double baseATK, CVector position, double angle)
:CMover_ShotBase(baseATK, CAttribute(0.0).NONE(40), position, 16, CVector(angle) * 3.0, 1, COF(0.0, 0.0, 0.0, 0.1), 0x00FFFF), cnt(0), pow(0.0) {
}

int CMover_Shot_Uniform_Homing::Update()
{
	cnt++;
	if (cnt > 240) {
		Status = 1;
		return Status;
	}

	pow += 0.5 * Constant::perFrame;
	baseATK *= 0.992;
	CVector v = getHomingAngle() * 6.0 - Velocity;
	if(getHomingAngle().getLength2() > Constant::zero_border)ApplyForce(v.getNorm() * pow);
	return Status;
}

void CMover_Shot_Uniform_Homing::Render() const
{
	CImageManager::getIns().find("shot_uniform_homing")->DrawRotaF(Position.x, Position.y, Velocity.getAngle(), 1.0, Constant::priority_shot);
}
