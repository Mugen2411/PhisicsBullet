#include "CMover_ShotBase.h"

CMover_ShotBase::CMover_ShotBase(CAttribute atk, CVector position, double size, CVector velocity, double mass, double frictionCF, double airresCF, double reflectCF)
	:CMover(MV_SHOT, position, size, velocity, mass, 0, frictionCF, airresCF, reflectCF, 0)
	,ATK(atk)
{
}

void CMover_ShotBase::Dispatch(std::shared_ptr<CMover> m)
{
	m->Hit(this);
}

void CMover_ShotBase::Hit(CMover_EnemyBase* m)
{
	Status = 1;
}
