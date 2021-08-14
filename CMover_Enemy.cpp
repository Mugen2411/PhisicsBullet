#include "CMover_Enemy.h"
#include "CEffectParent.h"
#include "CEffect_BulletDelete.h"

CMover_EnemyBase::CMover_EnemyBase(int Level, CAttribute attrDEF, int baseMoney, int color, CVector position, double accel, double maxSpeed):
	CMover(MV_ENEMY, position, 24.0, CVector(0.0, 0.0), 30, 1, 15, 25, 0.0, 0)
	,Accel(accel), MaxSpeed(maxSpeed), Direction(0), animCount(0),
	baseParams(Level), attrDEF(attrDEF), baseMoney(baseMoney), Color(color)
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

void CMover_EnemyBase::Dead()
{
	CEffectParent::RegisterEffect(std::make_shared<CEffect_BulletDelete>(Position, Velocity, Size+4, Color));
}

void CMover_EnemyBase::Disappear()
{
}

double CMover_EnemyBase::Damage(CAttribute shotATK)
{
	if (Status < 0)return 0.0;
	double ret = (shotATK / (attrDEF* baseParams.DEF)).Sum();
	baseParams.HP -= ret;
	if (baseParams.HP < 0) {
		Status = 1;
		Drop();
	}
	return ret;
}

void CMover_EnemyBase::Drop()
{
	//baseMoney*(1+baseParams.Level*0.01);
}

int CMover_EnemyBase::DamageColor(CAttribute shotATK)
{
	auto real = shotATK * attrDEF;
	if(real.Sum() - shotATK.Sum() > Constant::zero_border)return 2;
	if (real.Sum() - shotATK.Sum() < -Constant::zero_border)return 1;
	return 0;
}

void CMover_EnemyBase::Dispatch(std::shared_ptr<CMover> m)
{
	m->Hit(this);
}
