#include "CMover_Shot_Uniform_Homing.h"
#include "CImageManager.h"

CMover_Shot_Uniform_Homing::CMover_Shot_Uniform_Homing(double baseATK, CVector position, double angle)
:CMover_ShotBase(baseATK, CAttribute(0.0).NONE(30), position, 16, CVector(angle) * 1.0, 1, 0.2, 12, 0.0), cnt(0), pow(1.0) {
}

int CMover_Shot_Uniform_Homing::Update()
{
	cnt++;
	if (cnt > 240) {
		Status = 1;
		return Status;
	}

	pow += 1.0;
	baseATK *= 0.992;
	ApplyForce(getHomingAngle(4.0)*pow);
	return Status;
}

void CMover_Shot_Uniform_Homing::Render() const
{
	CImageManager::getIns().find("shot_uniform_homing")->DrawRotaF(Position.x, Position.y, Velocity.getAngle(), 1.0, -0.1);
}
