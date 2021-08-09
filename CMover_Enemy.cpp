#include "CMover_Enemy.h"

CMover_EnemyBase::CMover_EnemyBase(int Level, CAttribute attrDEF,CVector position, double accel, double maxSpeed):
	CMover(MV_ENEMY, position, 24.0, CVector(0.0, 0.0), 30, 1, 15, 25, 0.0, 0)
	,Accel(accel), MaxSpeed(maxSpeed), Direction(0), animCount(0), baseParams(Level), attrDEF(attrDEF)
{
}

void CMover_EnemyBase::Walk(CVector destination)
{
	CVector diff = (destination - Position).getNorm();
	double angle = diff.getAngle();
	Direction = diff.getDirection();
	if (diff.dot(Velocity)> MaxSpeed)return;
	Acceleration += diff * Accel;
}

double CMover_EnemyBase::Damage(CAttribute shotATK)
{
	double ret = (shotATK / (attrDEF* baseParams.DEF)).Sum();
	return ret;
}

void CMover_EnemyBase::Dispatch(std::shared_ptr<CMover> m)
{
	m->Hit(this);
}
