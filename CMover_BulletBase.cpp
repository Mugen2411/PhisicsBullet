#include "CMover_BulletBase.h"
#include "CImageManager.h"
#include "CEffectParent.h"
#include "CEffect_DamageNumber.h"
#include "CEffect_BulletDelete.h"
#include <DxLib.h>
#include "CAnchor.h"

CMover_BulletBase::CMover_BulletBase(CStatus baseparams, CAttribute atk, CVector position, double size, CVector velocity, double mass, COF cofs, int color = 0xFFFFFF)
	:CMover(MV_BULLET, position, size, velocity, mass, cofs, 0)
	,baseParams(baseparams), ATK(atk), color(color)
{
}

void CMover_BulletBase::BaseUpdate()
{
}

bool CMover_BulletBase::BaseRender() const
{
	auto p = CAnchor::getIns().getAnchoredPosition(Position);
	if (p.x + Size > 0 && p.x - Size < Constant::ScreenW && p.y + Size > 0 && p.y - Size < Constant::ScreenH)return true;
	return false;
}

void CMover_BulletBase::Dead()
{
	CEffectParent::RegisterEffect(std::make_shared<CEffect_BulletDelete>(Position, Velocity, Size, color));
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

void CMover_BulletBase::Hit(CMover_Player* m)
{
	m->Damage(ATK*baseParams.ATK, 0);
	m->ApplyForce(Velocity.getNorm() * Mass * Constant::Frame * Velocity.getLength2());
	Status = 1;
	CAnchor::getIns().Quake(2);
}
