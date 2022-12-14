#include "CMover_Player.h"
#include "CImageManager.h"
#include "CSoundManager.h"
#include <cmath>
#include <DxLib.h>
#include "CCostume_Festa.h"
#include "CCostume_Uniform.h"
#include "CEffectParent.h"
#include "CEffect_DamageNumber.h"
#include "CAnchor.h"
#include "CField.h"

CMover_Player::CMover_Player(CVector position, int level, CCostumeBase* costume)
	:CMover(MV_PLAYER, position, 24.0, CVector(0.0, 0.0), costume->Mass, costume->constants, 0), animCount(0.0)
	, input(CControllerFactory::getIns().getController())
	, Direction(1), Charge(0), State(0), baseParams(level), DigitHP(std::log10(baseParams.MaxHP)+1), waitDuration(0),
	costume(std::shared_ptr<CCostumeBase>(costume)), CND(), shotWait(0) {
	costume->setPlayer(this);
}

void CMover_Player::Walk()
{
	CVector v = input.lock()->getVector();
	CVector a = v * costume->MaxSpeed - Velocity;
	Acceleration += a.getNorm() * costume->Accelaration * std::sqrtl(nowFricted*Cofs.FrictionCF) * std::sqrtl(1 - (nowWatered * Cofs.WaterResCF));
}

void CMover_Player::BaseUpdate()
{
}

bool CMover_Player::BaseRender() const
{
	return true;
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
		animCount += costume->animSpeed;
		if (animCount > 3.0)animCount = 0.0;
	}
	else {
		animCount = 0.0;
	}
	Shot();
	Walk();

#ifdef _DEBUG
	printfDx("SP:%lf,%lf\nAP:%lf,%lf\n", p.x, p.y, Acceleration.x, Acceleration.y);
	printfDx("HP:%lf\n", baseParams.HP);
#endif
	return 0;
}

void CMover_Player::Shot()
{
	float angle = input.lock()->getMouseAngle(CAnchor::getIns().getAnchoredPosition(Position));
	int LPushTime = input.lock()->LClick(true);
	if (LPushTime == 0) {
		Charge++;
		Charge = min(costume->MaxCharge, Charge);
		return;
	}
	if (Charge == costume->MaxCharge) {
		costume->ChargeShot(baseParams.ATK, Position, angle);
		Charge = 0;
		shotWait = 0;
		Wait(costume->StrongShotDuration);
		return;
	}
	if (shotWait > costume->ShotRate) {
		shotWait = 0;
		costume->WeakShot(baseParams.ATK, Position, angle);
		Charge = 0;
	}
	shotWait++;
}

void CMover_Player::Render() const
{
	CImageManager::getIns().find(costume->GID)->DrawRota(Position.x, Position.y, 0.0, 1.0, 0.0, Direction * 4 + std::round(animCount));

	CAnchor::getIns().enableAbsolute();
	CImageManager::getIns().find("HPGuage")->DrawRotaFwithBlend(16 + 160, 16 + 8, 0, 1, 0xFFFFFF, DX_BLENDMODE_ALPHA, 108, 4, 2);
	CImageManager::getIns().find("HPGuage")->DrawRectwithBlend(16, 8, 320 * (baseParams.HP / baseParams.MaxHP), 32,
		0xffffff, DX_BLENDMODE_ALPHA, 192, 5, 1);
	CImageManager::getIns().find("HPGuage")->DrawRotaFwithBlend(16 + 160, 16 + 8, 0, 1, 0xFFFFFF, DX_BLENDMODE_ALPHA, 255, 6, 0);
	CND.Draw(16 + 160, 16 + 8, baseParams.HP, 0, 0, 7);
	//CND.Draw(16 + 48 + 16 * DigitHP, 16 + 8, baseParams.MaxHP, 0, 0, 2.3);
	CImageManager::getIns().find("aim")->DrawCircleGauge(input.lock()->MouseX(), input.lock()->MouseY(), (double)Charge / costume->MaxCharge, 7, 2);
	CImageManager::getIns().find("aim")->DrawRota(input.lock()->MouseX(), input.lock()->MouseY(), 0.0, 1.0, 7, (costume->MaxCharge == Charge) ? 1 : 0);
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
	double ret = ((BulletATK) / costume->AttributeDEF * 0.01).Sum();
	if (ret < Constant::zero_border)return;
	baseParams.HP -= ret;
	CSoundManager::getIns().find("player_hit")->Play(CSound::PLAYTYPE::PT_BACK);
	CEffectParent::RegisterEffect(std::make_shared<CEffect_DamageNumber>(Position - CVector(0.0, Size), ret, DamageColor(BulletATK), style));
}

void CMover_Player::RatioDamage(CAttribute BulletATK, int style)
{
	double ret = ((BulletATK * baseParams.MaxHP) / (costume->AttributeDEF * 100)).Sum();
	if (ret < Constant::zero_border)return;
	baseParams.HP -= ret;
	CSoundManager::getIns().find("player_hit")->Play(CSound::PLAYTYPE::PT_BACK);
	CEffectParent::RegisterEffect(std::make_shared<CEffect_DamageNumber>(Position - CVector(0.0, Size), ret, DamageColor(BulletATK), style));
}

int CMover_Player::DamageColor(CAttribute shotATK)
{
	auto real = shotATK / costume->AttributeDEF;
	if (real.Sum() - shotATK.Sum() > Constant::zero_border)return 1;
	if (real.Sum() - shotATK.Sum() < -Constant::zero_border)return 2;
	return 0;
}

void CMover_Player::RegisterShot(std::shared_ptr<CMover_ShotBase> s)
{
	med->RegisterMover(s);
}

void CMover_Player::Hit(CMover_EnemyBase* m)
{
	m->ApplyForce(Acceleration * 0.1 * Mass);
	CVector delta = (m->getPosition() - Position).getLength2() < 4 ? CVector(GetRand(10) - 5, GetRand(10) - 5) * 0.02 : CVector(0.0, 0.0);
	m->ApplyForce((m->getPosition() - Position + delta).getNorm() * Mass);
}

void CMover_Player::FieldDispatch(CField* f) {
}