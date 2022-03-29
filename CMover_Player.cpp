#include "CMover_Player.h"
#include "CImageManager.h"
#include <cmath>
#include <DxLib.h>
#include "CMover_Shot_Uniform_Homing.h"
#include "CCostume_Uniform.h"
#include "CEffectParent.h"
#include "CEffect_DamageNumber.h"
#include "CAnchor.h"

CMover_Player::CMover_Player(CVector position)
	:CMover(MV_PLAYER, position, 16.0, CVector(0.0, 0.0), 30, 15, 25, 0.0, 0), animCount(0.0)
	, input(CControllerFactory::getIns().getController())
	, Direction(1), Charge(0), State(0), baseParams(0), waitDuration(0), costume(std::make_shared<CCostume_Uniform>(this)) {
}

void CMover_Player::Walk()
{
	CVector v = input.lock()->getVector() * costume->getAccelaration() * nowFricted;
	if (v.x < 0) {
		if (Velocity.x > 0)Acceleration.x += v.x;
		else if (-Velocity.x < costume->getMaxSpeed())Acceleration.x += v.x;
	}
	else {
		if (Velocity.x < 0)Acceleration.x += v.x;
		else if (Velocity.x < costume->getMaxSpeed())Acceleration.x += v.x;
	}
	if (v.y < 0) {
		if (Velocity.y > 0)Acceleration.y += v.y;
		else if (-Velocity.y < costume->getMaxSpeed())Acceleration.y += v.y;
	}
	else {
		if (Velocity.y < 0)Acceleration.y += v.y;
		else if (Velocity.y < costume->getMaxSpeed())Acceleration.y += v.y;
	}
}

int CMover_Player::Update()
{
	auto p = CAnchor::getIns().getAnchoredPosition(Position);
	if (p.x < Constant::ScrollMargin)CAnchor::getIns().setPosition(CVector(Position.x - Constant::ScrollMargin, CAnchor::getIns().getAnchorY()));
	if (p.x > Constant::ScreenW - Constant::ScrollMargin)CAnchor::getIns().setPosition(CVector(Position.x - Constant::ScreenW + Constant::ScrollMargin, CAnchor::getIns().getAnchorY()));

	if (p.y < Constant::ScrollMargin)CAnchor::getIns().setPosition(CVector(CAnchor::getIns().getAnchorX(), Position.y - Constant::ScrollMargin));
	if (p.y > Constant::ScreenH - Constant::ScrollMargin)CAnchor::getIns().setPosition(CVector(CAnchor::getIns().getAnchorX(), Position.y - Constant::ScreenH + Constant::ScrollMargin));

	if (State == 1) {
		waitDuration--;
		if (waitDuration == 0)State = 0;
		return 0;
	}
	if (input.lock()->isChanged() > 0) {
		Direction = input.lock()->getDirection();
		animCount += costume->getAnimSpeed();
		if (animCount > 3.0)animCount = 0.0;
	}
	else {
		animCount = 0.0;
	}
	Shot();
	Walk();

#ifdef _DEBUG
	printfDx("SP:%lf,%lf\nAP:%lf,%lf\n", p.x, p.y, Acceleration.x, Acceleration.y);
#endif
	return 0;
}

void CMover_Player::Shot()
{
	float angle = input.lock()->getMouseAngle(CAnchor::getIns().getAnchoredPosition(Position));
	int LPushTime = input.lock()->LClick(true);
	if (LPushTime == 0) {
		Charge++;
		Charge = min(costume->getMaxCharge(), Charge);
		return;
	}
	if (Charge == costume->getMaxCharge()) {
		med.lock()->RegisterMover(costume->ChargeShot(baseParams.ATK, Position+CVector(cos(angle)*16, sin(angle)*16), angle));
		Charge = 0;
		Wait(costume->getStrongShotDuration());
		return;
	}
	if (LPushTime % costume->getShotRate() == 1) {
		med.lock()->RegisterMover(costume->WeakShot(baseParams.ATK, Position, angle));
		Charge = 0;
	}
}

void CMover_Player::Render() const
{
	CImageManager::getIns().find("player_komuk")->DrawRota(Position.x, Position.y, 0.0, 1.0, 0.0, Direction * 4 + std::round(animCount));

	CAnchor::getIns().enableAbsolute();
	CImageManager::getIns().find("HPGuage")->DrawRotaFwithBlend(16 + 160, 16 + 8, 0, 1, 0xFFFFFF, DX_BLENDMODE_ALPHA, 108, 2.0, 2);
	CImageManager::getIns().find("HPGuage")->DrawExtendWithBlend(16, 8, 16 + 320 * (baseParams.HP / baseParams.MaxHP), 40,
		0xffffff, DX_BLENDMODE_ALPHA, 192, 2.1, 1);
	CImageManager::getIns().find("HPGuage")->DrawRotaFwithBlend(16 + 160, 16 + 8, 0, 1, 0xFFFFFF, DX_BLENDMODE_ALPHA, 255, 2.2, 0);
	CImageManager::getIns().find("aim")->DrawCircleGauge(input.lock()->MouseX(), input.lock()->MouseY(), (double)Charge / costume->getMaxCharge(), 0.9, 2);
	CImageManager::getIns().find("aim")->DrawRota(input.lock()->MouseX(), input.lock()->MouseY(), 0.0, 1.0, 1.0, (costume->getMaxCharge() == Charge)? 1 : 0);
	CAnchor::getIns().disableAbsolute();
}

void CMover_Player::Dead()
{
}

void CMover_Player::Disappear()
{
}

void CMover_Player::Wait(int duration)
{
	State = 1;
	waitDuration = duration;
}

void CMover_Player::Damage(CAttribute BulletATK, int style)
{
	double ret = ((BulletATK) / (baseParams.DEF)).Sum();
	if (ret < Constant::zero_border)return;
	baseParams.HP -= ret;
	CEffectParent::RegisterEffect(std::make_shared<CEffect_DamageNumber>(Position - CVector(0.0, Size), ret, DamageColor(BulletATK), style));
}

void CMover_Player::RatioDamage(CAttribute BulletATK, int style)
{
	double ret = ((BulletATK * baseParams.MaxHP) / (costume->AttributeDEF * 100)).Sum();
	if (ret < Constant::zero_border)return;
	baseParams.HP -= ret;
	CEffectParent::RegisterEffect(std::make_shared<CEffect_DamageNumber>(Position - CVector(0.0, Size), ret, DamageColor(BulletATK), style));
}

void CMover_Player::HitDispatch(std::shared_ptr<CMover> m)
{
	m->Hit(this);
}

int CMover_Player::DamageColor(CAttribute shotATK)
{
	auto real = shotATK / costume->AttributeDEF;
	if (real.Sum() - shotATK.Sum() > Constant::zero_border)return 1;
	if (real.Sum() - shotATK.Sum() < -Constant::zero_border)return 2;
	return 0;
}

void CMover_Player::Hit(CMover_EnemyBase* m)
{
	ApplyForce((Position - m->getPosition()).getNorm() * 16 * Mass / max(0.3, (Position - m->getPosition()).getLength()));
}
