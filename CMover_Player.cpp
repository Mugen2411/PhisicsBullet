#include "CMover_Player.h"
#include "CImageManager.h"
#include <cmath>
#include <DxLib.h>
#include "CMover_Shot_Uniform_Homing.h"
#include "CCostume_Uniform.h"
#include "CEffectParent.h"
#include "CEffect_DamageNumber.h"

CMover_Player::CMover_Player(CVector position)
	:CMover(MV_PLAYER, position,	24.0, CVector(0.0, 0.0),30, 15, 25, 0.0, 0), animCount(0.0)
	, input(CControllerFactory::getIns().getController())
	,Direction(1), Charge(0), State(0), baseParams(0), costume(std::make_shared<CCostume_Uniform>()) {
}

void CMover_Player::Walk()
{
	CVector v = input->getVector() * costume->getAccelaration() * nowFricted;
	if (v.x < 0) {
		if (Velocity.x > 0)Acceleration.x += v.x;
		else if(-Velocity.x < costume->getMaxSpeed())Acceleration.x += v.x;
	}else {
		if (Velocity.x < 0)Acceleration.x += v.x;
		else if (Velocity.x < costume->getMaxSpeed())Acceleration.x += v.x;
	}
	if (v.y < 0) {
		if (Velocity.y > 0)Acceleration.y += v.y;
		else if(-Velocity.y < costume->getMaxSpeed())Acceleration.y += v.y;
	}else {
		if (Velocity.y < 0)Acceleration.y += v.y;
		else if (Velocity.y < costume->getMaxSpeed())Acceleration.y += v.y;
	}
}

int CMover_Player::Update()
{
	if (input->update() > 0) {
		Direction = input->getDirection();
		animCount += costume->getAnimSpeed();
		if (animCount > 3.0)animCount = 0.0;
	}
	else {
		animCount = 0.0;
	}
	Shot();
	Walk();
	
#ifdef _DEBUG
	printfDx("V:%lf,%lf\nA:%lf,%lf\n", Velocity.x, Velocity.y, Acceleration.x, Acceleration.y);
#endif
	return 0;
}

void CMover_Player::Shot()
{
	float angle = input->getMouseAngle(Position);
	int LPushTime = input->LClick(true);
	if (LPushTime == 0) {
		Charge++;
		Charge %= costume->getMaxCharge();
		return;
	}
	if (Charge == costume->getMaxCharge() - 1) {
		med.lock()->RegisterMover(costume->ChargeShot(baseParams.ATK, Position, angle));
		Charge = 0;
		return;
	}
	if (LPushTime % costume->getShotRate() == 1)med.lock()->RegisterMover(costume->WeakShot(baseParams.ATK, Position, angle));
}

void CMover_Player::Render() const
{
	CImageManager::getIns().find("player_komuk")->DrawRota(Position.x, Position.y, 0.0, 1.0, 0.0,Direction*4+std::round(animCount));
	CImageManager::getIns().find("aim")->DrawRota(input->MouseX(), input->MouseY(), 0.0, 1.0, 1.0);
}

void CMover_Player::Dead()
{
}

void CMover_Player::Disappear()
{
}

void CMover_Player::Damage(CAttribute BulletATK, int style)
{
	double ret = (BulletATK / (baseParams.DEF)).Sum();
	baseParams.HP -= ret;
	CEffectParent::RegisterEffect(std::make_shared<CEffect_DamageNumber>(Position, ret, DamageColor(BulletATK), style));
}

void CMover_Player::HitDispatch(std::shared_ptr<CMover> m)
{
	m->Hit(this);
}

int CMover_Player::DamageColor(CAttribute shotATK)
{
	auto real = shotATK * costume->AttributeDEF;
	if (real.Sum() - shotATK.Sum() > Constant::zero_border)return 2;
	if (real.Sum() - shotATK.Sum() < -Constant::zero_border)return 1;
	return 0;
}