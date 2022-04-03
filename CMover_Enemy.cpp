#include "CMover_Enemy.h"
#include "CMover_Player.h"
#include "CEffectParent.h"
#include "CEffect_BulletDelete.h"
#include "CEffect_MoneyNumber.h"
#include "CEffect_DamageNumber.h"
#include "CImageManager.h"
#include "CAnchor.h"

CMover_EnemyBase::CMover_EnemyBase(double Mass, int Level, double atkCF, double defCF, double hpCF, CAttribute attrDEF, int baseMoney,
	int color, CVector position, double accel, double maxSpeed, double frictionCF, double airresCF, double waterCF) :
	CMover(MV_ENEMY, position, 24.0, CVector(0.0, 0.0), Mass, frictionCF, airresCF, waterCF, 0.0, 0)
	, Accel(accel), MaxSpeed(maxSpeed), Direction(0), animCount(0),
	baseParams(Level, atkCF, defCF, hpCF), attrDEF(attrDEF), baseMoney(baseMoney), Color(color)
{
}

void CMover_EnemyBase::Walk(CVector destination)
{
	CVector diff = (destination - Position).getNorm();
	double angle = diff.getAngle();
	Direction = diff.getDirection();
	if (diff.dot(Velocity) > MaxSpeed)return;
	Acceleration += diff * Accel * nowFricted * Constant::Frame;
}

void CMover_EnemyBase::Move_on_Route()
{
	if (route.empty()) {
		Find_Route();
		return;
	}
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

void CMover_EnemyBase::BaseUpdate()
{
}

bool CMover_EnemyBase::BaseRender() const
{
	/*for (auto& i : route) {
		CImageManager::getIns().find("editor_cursor")->DrawRota(i.x, i.y, 0, 1, 1.0);
	}*/
	auto p = CAnchor::getIns().getAnchoredPosition(Position);
	CAnchor::getIns().enableAbsolute();
	if (p.x + Size < 0) {
		if (p.y + Size < 0) {
			CImageManager::getIns().find("enemy_marker")->DrawRota(8, 8, (CVector(0, 0) - p).getAngle(), 1.0, 0.9);
			CAnchor::getIns().disableAbsolute();
			return false;
		}
		if (p.y - Size > Constant::ScreenH) {
			CImageManager::getIns().find("enemy_marker")->DrawRota(8, Constant::ScreenH - 8, (CVector(0, Constant::ScreenH) - p).getAngle(), 1.0, 0.9);
			CAnchor::getIns().disableAbsolute();
			return false;
		}
		CImageManager::getIns().find("enemy_marker")->DrawRota(8, p.y, 0.0, 1.0, 0.9);
		CAnchor::getIns().disableAbsolute();
		return false;
	}
	if (p.x - Size > Constant::ScreenW) {
		if (p.y + Size < 0) {
			CImageManager::getIns().find("enemy_marker")->DrawRota(Constant::ScreenW - 8, 8, (CVector(Constant::ScreenW, 0) - p).getAngle(), 1.0, 0.9);
			CAnchor::getIns().disableAbsolute();
			return false;
		}
		if (p.y - Size > Constant::ScreenH) {
			CImageManager::getIns().find("enemy_marker")->DrawRota(Constant::ScreenW - 8, Constant::ScreenH - 8, (CVector(Constant::ScreenW, Constant::ScreenH) - p).getAngle(), 1.0, 0.9);
			CAnchor::getIns().disableAbsolute();
			return false;
		}
		CImageManager::getIns().find("enemy_marker")->DrawRota(Constant::ScreenW - 8, p.y, Constant::PI, 1.0, 0.9);
		CAnchor::getIns().disableAbsolute();
		return false;
	}
	if (p.y + Size < 0) {
		CImageManager::getIns().find("enemy_marker")->DrawRota(p.x, 8, -Constant::PI / 2, 1.0, 0.9);
		CAnchor::getIns().disableAbsolute();
		return false;
	}
	if (p.y - Size > Constant::ScreenH) {
		CImageManager::getIns().find("enemy_marker")->DrawRota(p.x, Constant::ScreenH - 8, Constant::PI / 2, 1.0, 0.9);
		CAnchor::getIns().disableAbsolute();
		return false;
	}
	CAnchor::getIns().disableAbsolute();
	Render_HPGuage();
	return true;
}

void CMover_EnemyBase::Dead()
{
	for (int i = 0; i < 3; i++)CEffectParent::RegisterEffect(
		std::make_shared<CEffect_BulletDelete>(
			Position + CVector(GetRand(100) * 0.2 - 10, GetRand(100) * 0.2 - 10),
			Velocity, Size + 4 - GetRand(8), Color));

	CAnchor::getIns().Quake(12);
}

void CMover_EnemyBase::Disappear()
{
}

void CMover_EnemyBase::Render_HPGuage()const
{
	CImageManager::getIns().find("enemy_HPGuage")->DrawExtendWithBlend(Position.x - 16, Position.y - Size - 8,
		Position.x + 16, Position.y - Size - 4, 0xFFFFFF, DX_BLENDMODE_ALPHA, 108, 1.1, 1);
	CImageManager::getIns().find("enemy_HPGuage")->DrawExtendWithBlend(Position.x - 16, Position.y - Size - 8,
		Position.x - 16 + 32 * (baseParams.HP / baseParams.MaxHP), Position.y - Size - 4, 0xFFFFFF, DX_BLENDMODE_ALPHA, 160, 1.2, 0);

}

void CMover_EnemyBase::Damage(CAttribute shotATK, int style)
{
	if (Status < 0)return;
	double ret = (shotATK / (attrDEF * baseParams.DEF)).Sum();
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
	if (real.Sum() - shotATK.Sum() > Constant::zero_border)return 2;
	if (real.Sum() - shotATK.Sum() < -Constant::zero_border)return 1;
	return 0;
}

void CMover_EnemyBase::Hit(CMover_EnemyBase* m)
{
	m->ApplyForce((m->getPosition() - Position + CVector(GetRand(10) - 5, GetRand(10) - 5) * 0.01).getNorm() * Mass * Size);
}

void CMover_EnemyBase::Hit(CMover_Player* m)
{
	//m->ApplyForce(Acceleration.getNorm() * Acceleration.getLength() * Mass);
	m->ApplyForce((m->getPosition() - Position).getNorm() * Mass * Size);
}
