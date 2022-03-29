#include "CMover_Enemy.h"
#include "CMover_Player.h"
#include "CEffectParent.h"
#include "CEffect_BulletDelete.h"
#include "CEffect_MoneyNumber.h"
#include "CEffect_DamageNumber.h"
#include "CImageManager.h"

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

void CMover_EnemyBase::Move_on_Route()
{
	if (route.empty())return;
	if ((Position - route.back()).getLength2() < 8 * 8) {
		route.pop_back();
		return;
	}
	Walk(route.back());
}

void CMover_EnemyBase::Find_Route()
{
	route = med.lock()->GetRoute(Position, med.lock()->GetPlayerPosition(), attrDEF);
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

void CMover_EnemyBase::Render_HPGuage()const
{
	CImageManager::getIns().find("enemy_HPGuage")->DrawExtendWithBlend(Position.x - 16, Position.y - Size - 8,
		Position.x + 16, Position.y - Size - 4, 0xFFFFFF, DX_BLENDMODE_ALPHA, 192, -1.0, 1);
	CImageManager::getIns().find("enemy_HPGuage")->DrawExtendWithBlend(Position.x - 16, Position.y - Size - 8,
		Position.x - 16 + 32*(baseParams.HP / baseParams.MaxHP), Position.y - Size - 4, 0xFFFFFF, DX_BLENDMODE_ALPHA, 192, -1.0, 0);

}

void CMover_EnemyBase::Damage(CAttribute shotATK, int style)
{
	if (Status < 0)return;
	double ret = (shotATK / (attrDEF* baseParams.DEF)).Sum();
	if (ret < Constant::zero_border)return;
	baseParams.HP -= ret;
	CEffectParent::RegisterEffect(std::make_shared<CEffect_DamageNumber>(Position - CVector(0.0, Size), ret, DamageColor(shotATK), style));
	if (baseParams.HP < 0) {
		Status = 1;
		Drop();
	}
}

void CMover_EnemyBase::RatioDamage(CAttribute shotATK, int style)
{
	if (Status < 0)return;
	double ret = ((shotATK * baseParams.MaxHP) / (attrDEF * 100)).Sum();
	if (ret < Constant::zero_border)return;
	baseParams.HP -= ret;
	CEffectParent::RegisterEffect(std::make_shared<CEffect_DamageNumber>(Position - CVector(0.0, Size), ret, DamageColor(shotATK), style));
	if (baseParams.HP < 0) {
		Status = 1;
		Drop();
	}
}

void CMover_EnemyBase::Drop()
{
	int val = std::ceil(baseMoney * (1 + baseParams.Level * 0.1)) + (baseParams.Level / 5.0);
	med.lock()->getMoney(val);
	CEffectParent::RegisterEffect(std::make_shared<CEffect_MoneyNumber>(Position - CVector(0.0, Size), val));
}

int CMover_EnemyBase::DamageColor(CAttribute shotATK)
{
	auto real = shotATK * attrDEF;
	if(real.Sum() - shotATK.Sum() > Constant::zero_border)return 2;
	if (real.Sum() - shotATK.Sum() < -Constant::zero_border)return 1;
	return 0;
}

void CMover_EnemyBase::HitDispatch(std::shared_ptr<CMover> m)
{
	m->Hit(this);
}

void CMover_EnemyBase::Hit(CMover_EnemyBase* m)
{
	CVector f = (Position - m->Position).getNorm() * 0.5;
	Velocity += f;
	m->Velocity -= f;
}

void CMover_EnemyBase::Hit(CMover_Player* m)
{
	ApplyForce((Position - m->getPosition()).getNorm() * 32 * Mass / max(0.1, (Position - m->getPosition()).getLength()));
}
