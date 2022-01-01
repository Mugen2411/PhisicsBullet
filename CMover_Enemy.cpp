#include "CMover_Enemy.h"
#include "CEffectParent.h"
#include "CEffect_BulletDelete.h"
#include "CEffect_MoneyNumber.h"

CMover_EnemyBase::CMover_EnemyBase(int Level, double atkCF, double defCF, double hpCF, CAttribute attrDEF, int baseMoney, int color, CVector position, double accel, double maxSpeed):
	CMover(MV_ENEMY, position, 24.0, CVector(0.0, 0.0), 30, 15, 25, 0.0, 0)
	,Accel(accel), MaxSpeed(maxSpeed), Direction(0), animCount(0),
	baseParams(Level, atkCF, defCF, hpCF), attrDEF(attrDEF), baseMoney(baseMoney), Color(color)
{
}

void CMover_EnemyBase::Walk(CVector destination)
{
	CVector diff = (destination - Position).getNorm();
	double angle = diff.getAngle();
	Direction = diff.getDirection();
	if (diff.dot(Velocity)> MaxSpeed)return;
	Acceleration += diff * Accel * nowFricted;
}

void CMover_EnemyBase::Dead()
{
	for(int i=0;i<3;i++)CEffectParent::RegisterEffect(
		std::make_shared<CEffect_BulletDelete>(
			Position+CVector(GetRand(100)*0.2-10, GetRand(100) * 0.2-10), 
			Velocity, Size+4-GetRand(8), Color));
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
	int val = std::ceil(baseMoney * (1 + baseParams.Level * 0.01)) + baseParams.Level;
	med.lock()->getMoney(val);
	CEffectParent::RegisterEffect(std::make_shared<CEffect_MoneyNumber>(Position+CVector(0.0, 10.0), val));
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
