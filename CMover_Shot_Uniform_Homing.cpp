#include "CMover_Shot_Uniform_Homing.h"
#include "CImageManager.h"

CMover_Shot_Uniform_Homing::CMover_Shot_Uniform_Homing(CVector position, float angle)
:CMover_ShotBase(CAttribute(0.5,0,0,0,0,0), position, 16, CVector(angle)*1.0, 4, 0.2, 12, 0.0), cnt(0), pow(1.0){
}

int CMover_Shot_Uniform_Homing::Update()
{
	cnt++;
	if (cnt > 240) {
		Status = 2;
		return Status;
	}

	pow += 1.0;
	if (!target.lock()) {
		target = med.lock()->GetNearestMover(CMover::MOVER_ID::MV_ENEMY, Position);
		return Status;
	}
	ApplyForce((target.lock()->getPosition() - (Position+Velocity)).getNorm()*pow);
	return Status;
}

void CMover_Shot_Uniform_Homing::Render() const
{
	CImageManager::getIns().find("shot_uniform_homing")->DrawRotaF(Position.x, Position.y, Velocity.getAngle(), 1.0, -0.1);
}

void CMover_Shot_Uniform_Homing::Dead()
{
}

void CMover_Shot_Uniform_Homing::Disappear()
{
}
