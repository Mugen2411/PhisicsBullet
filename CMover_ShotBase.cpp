#include "CMover_ShotBase.h"
#include "CEffectParent.h"
#include "CEffect_DamageNumber.h"

CMover_ShotBase::CMover_ShotBase(CStatus baseparams, CAttribute atk, CVector position, double size, CVector velocity, double mass, double frictionCF, double airresCF, double reflectCF)
	:CMover(MV_SHOT, position, size, velocity, mass, 0, frictionCF, airresCF, reflectCF, 0)
	,ATK(atk), baseParams(baseparams)
{
}

void CMover_ShotBase::Dispatch(std::shared_ptr<CMover> m)
{
	m->Hit(this);
}

void CMover_ShotBase::Hit(CMover_EnemyBase* m)
{
	double Damage = m->Damage(ATK * baseParams.ATK);
	CEffectParent::RegisterEffect(std::make_shared<CEffect_DamageNumber>(Position, Damage, 0, 1));
	Status = 1;
}
