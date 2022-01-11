#include "CMover_BulletBase.h"
#include "CImageManager.h"
#include "CEffectParent.h"
#include "CEffect_DamageNumber.h"
#include "CEffect_BulletDelete.h"
#include <DxLib.h>

CMover_BulletBase::CMover_BulletBase(CStatus baseparams, CAttribute atk, CVector position, double size, CVector velocity, double mass, double frictionCF, double airresCF, double reflectCF)
	:CMover(MV_BULLET, position, size, velocity, mass, frictionCF, airresCF, reflectCF, 0)
	,baseParams(baseparams), ATK(atk)
{
}

void CMover_BulletBase::Dead()
{
	CEffectParent::RegisterEffect(std::make_shared<CEffect_BulletDelete>(Position, Velocity, Size, 0xFF0000));
}

void CMover_BulletBase::Disappear()
{
}

void CMover_BulletBase::Damage(CAttribute shotATK, int style)
{
}

void CMover_BulletBase::RatioDamage(CAttribute shotATK, int style)
{
}

void CMover_BulletBase::HitDispatch(std::shared_ptr<CMover> m)
{
	m->Hit(this);
}

void CMover_BulletBase::Hit(CMover_Player* m)
{
	m->Damage(ATK*baseParams.ATK, 0);
	m->ApplyForce(Velocity.getNorm() * Mass * Constant::Frame * Velocity.getLength2());
	Status = 1;
}
