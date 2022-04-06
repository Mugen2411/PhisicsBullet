#include "CMover_ShotBase.h"
#include "CEffectParent.h"
#include "CEffect_DamageNumber.h"
#include "CEffect_BulletDelete.h"
#include "CAnchor.h"

CMover_ShotBase::CMover_ShotBase(double baseATK, CAttribute atk, CVector position, double size, CVector velocity, double mass, COF cofs)
	:CMover(MV_SHOT, position, size, velocity, mass, cofs, 0)
	,ATK(atk), baseATK(baseATK),cnt(0)
{
}

void CMover_ShotBase::BaseUpdate()
{
	cnt++;
}

bool CMover_ShotBase::BaseRender() const
{
	auto p = CAnchor::getIns().getAnchoredPosition(Position);
	if (p.x + Size > 0 && p.x - Size < Constant::ScreenW && p.y + Size > 0 && p.y - Size < Constant::ScreenH)return true;
	return false;
}

void CMover_ShotBase::Dead()
{
	CEffectParent::RegisterEffect(std::make_shared<CEffect_BulletDelete>(Position, Velocity, Size, 0x00FFFF));
}

void CMover_ShotBase::Disappear()
{
}

void CMover_ShotBase::Damage(CAttribute shotATK, int style)
{
}

void CMover_ShotBase::RatioDamage(CAttribute shotATK, int style)
{
}

CVector CMover_ShotBase::getHomingAngle(double maxSpeed)
{
	if (!target.lock()) {
		target = med.lock()->GetNearestMover(CMover::MOVER_ID::MV_ENEMY, Position);
		return CVector(0.0, 0.0);
	}
	auto diff = (target.lock()->getPosition() - (Position + Velocity)).getNorm();
	if (diff.dot(Velocity) > maxSpeed) {
		return diff - Velocity.getNorm();
	}

	return diff;
}

void CMover_ShotBase::Hit(CMover_EnemyBase* m)
{
	m->Damage(ATK * baseATK, 1);
	m->ApplyForce(Velocity.getNorm() * Mass * Constant::Frame * Velocity.getLength2());
	Status = 1;
}

void CMover_ShotBase::ifonWall()
{
	Status = 1;
}
