#include "CMover_Enemy.h"
#include "CMover_Player.h"
#include "CEffectParent.h"
#include "CEffect_EnemyDelete.h"
#include "CEffect_MoneyNumber.h"
#include "CEffect_DamageNumber.h"
#include "CImageManager.h"
#include "CSoundManager.h"
#include "CAnchor.h"
#include "CPassiveSkill.h"

CMover_EnemyBase::CMover_EnemyBase(double Mass, int Level, double atkCF, double hpCF, CAttribute attrDEF, int baseMoney,
	int color, CVector position, double accel, double maxSpeed, COF cofs) :
	CMover(MV_ENEMY, position, 24.0, CVector(0.0, 0.0), Mass, cofs, 0)
	, Accel(accel), MaxSpeed(maxSpeed), Direction(0), animCount(0),
	baseParams(Level, atkCF, hpCF), attrDEF(attrDEF), baseMoney(baseMoney), Color(color), seed(), rand(seed()), pushed(0)
{
}

void CMover_EnemyBase::Walk(CVector destination)
{
	CVector diff = (destination - Position).getNorm() * MaxSpeed;
	CVector v = diff - Velocity;
	Acceleration += v.getNorm() * min(v.getLength(), 1.0) * Accel * std::sqrtl(nowFricted * Cofs.FrictionCF) * std::sqrtl(1 - (nowWatered * Cofs.WaterResCF));
	Direction = diff.getDirection();
}

void CMover_EnemyBase::Move_on_Route()
{
	if (route.empty()) {
		return;
	}
	if ((Position - route.front()).getLength2() < 8 * 8) {
		route.pop_front();
		return;
	}
	Walk(route.front());
}

void CMover_EnemyBase::Find_Route(int distance)
{
	if (!med)return;
	route = med->GetRoute(Position, med->GetPlayerPosition(), attrDEF, distance);
}

void CMover_EnemyBase::findTargetByDistance(int distance)
{
	if (!med)return;
	std::vector<CVector> dists = med->GetTargetByDistance(med->GetPlayerPosition(), distance);
	std::uniform_int_distribution<> r(0, dists.size() - 1);
	CVector target = dists[r(rand)];
	route = med->GetRoute(Position, target, attrDEF, 0);
}

void CMover_EnemyBase::BaseUpdate()
{
	pushed = 0;
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
			CImageManager::getIns().find("enemy_marker")->DrawRota(8, 8, (p - CVector(0, 0)).getAngle(), 1.0, Constant::priority_marker);
			CAnchor::getIns().disableAbsolute();
			return false;
		}
		if (p.y - Size > Constant::ScreenH) {
			CImageManager::getIns().find("enemy_marker")->DrawRota(8, Constant::ScreenH - 8, (p - CVector(0, Constant::ScreenH)).getAngle(), 1.0, Constant::priority_marker);
			CAnchor::getIns().disableAbsolute();
			return false;
		}
		CImageManager::getIns().find("enemy_marker")->DrawRota(8, p.y, Constant::PI, 1.0, Constant::priority_marker);
		CAnchor::getIns().disableAbsolute();
		return false;
	}
	if (p.x - Size > Constant::ScreenW) {
		if (p.y + Size < 0) {
			CImageManager::getIns().find("enemy_marker")->DrawRota(Constant::ScreenW - 8, 8, (p - CVector(Constant::ScreenW, 0)).getAngle(), 1.0, Constant::priority_marker);
			CAnchor::getIns().disableAbsolute();
			return false;
		}
		if (p.y - Size > Constant::ScreenH) {
			CImageManager::getIns().find("enemy_marker")->DrawRota(Constant::ScreenW - 8, Constant::ScreenH - 8, (p - CVector(Constant::ScreenW, Constant::ScreenH)).getAngle(), 1.0, Constant::priority_marker);
			CAnchor::getIns().disableAbsolute();
			return false;
		}
		CImageManager::getIns().find("enemy_marker")->DrawRota(Constant::ScreenW - 8, p.y, Constant::PI * 3, 1.0, Constant::priority_marker);
		CAnchor::getIns().disableAbsolute();
		return false;
	}
	if (p.y + Size < 0) {
		CImageManager::getIns().find("enemy_marker")->DrawRota(p.x, 8, -Constant::PI / 2, 1.0, Constant::priority_marker);
		CAnchor::getIns().disableAbsolute();
		return false;
	}
	if (p.y - Size > Constant::ScreenH) {
		CImageManager::getIns().find("enemy_marker")->DrawRota(p.x, Constant::ScreenH - 8, Constant::PI / 2, 1.0, Constant::priority_marker);
		CAnchor::getIns().disableAbsolute();
		return false;
	}
	CAnchor::getIns().disableAbsolute();
	Render_HPGuage();
	return true;
}

void CMover_EnemyBase::Dead()
{
	for (int i = 0; i < 5; i++)CEffectParent::RegisterEffect(
		std::make_shared<CEffect_EnemyDelete>(
			Position + CVector(GetRand(Size * 3) - Size * 1.5, GetRand(Size * 3) - Size * 1.5),
			Size * 0.5 + GetRand(Size * 1.5), Color, 30));
	for (int i = 0; i < 2; i++)CEffectParent::RegisterEffect(
		std::make_shared<CEffect_EnemyDelete>(
			Position, Size * (4 + i * 1.0), Color, 12));

	CAnchor::getIns().Quake(15, 3.0);
	CSoundManager::getIns().find("enemy_kill")->Play(CSound::PT_BACK);
}

void CMover_EnemyBase::Disappear()
{
}

void CMover_EnemyBase::Render_HPGuage()const
{
	CImageManager::getIns().find("enemy_HPGuage")->DrawExtendWithBlend(Position.x - 16, Position.y - Size - 8,
		Position.x + 16, Position.y - Size - 4, 0xFFFFFF, DX_BLENDMODE_ALPHA, 108, Constant::priority_marker, 1);
	CImageManager::getIns().find("enemy_HPGuage")->DrawExtendWithBlend(Position.x - 16, Position.y - Size - 8,
		Position.x - 16 + 32 * (baseParams.HP / baseParams.MaxHP), Position.y - Size - 4, 0xFFFFFF, DX_BLENDMODE_ALPHA, 160, Constant::priority_marker, 0);

}

void CMover_EnemyBase::Damage(CAttribute shotATK, int style)
{
	if (Status < 0)return;
	double ret = (shotATK / attrDEF * 0.01).Sum();
	if (ret < Constant::zero_border)return;
	baseParams.HP -= ret;
	CEffectParent::RegisterEffect(std::make_shared<CEffect_DamageNumber>(Position - CVector(0.0, Size), ret, DamageColor(shotATK), style));
	CSoundManager::getIns().find("enemy_hit")->Play(CSound::PLAYTYPE::PT_BACK);
	if (baseParams.HP < 0) {
		setStatus(STATUS::DEAD);
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
		setStatus(STATUS::DEAD);
		Drop();
	}
}

void CMover_EnemyBase::Drop()
{
	int val = std::ceil(baseMoney * (1.0 + (int)(baseParams.Level / 15.0) * 0.1) + (baseParams.Level));
	if (auto r = med)r->getMoney(val*CPassiveSkill::getIns().getMoneyMult());
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
	pushed++;
	CVector diff = m->getPosition() - Position;
	CVector delta = diff.getLength2() < Constant::zero_border ? CVector(Constant::PI2 / 64 * GetRand(64)) : CVector(0.0, 0.0);
	m->ApplyForce((diff + delta).getNorm() * Mass / pushed);
}

void CMover_EnemyBase::Hit(CMover_Player* m)
{
	CVector diff = m->getPosition() - Position;
	CVector delta = CVector(Constant::PI2 / 64 * GetRand(64));
	m->ApplyForce((diff + delta).getNorm() * Mass);
	m->ApplyForce(Velocity * Mass);
}
