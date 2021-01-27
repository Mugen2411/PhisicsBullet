#include "CMover_Player.h"
#include "CImageManager.h"
#include <cmath>
#include <DxLib.h>

CMover_Player::CMover_Player(CVector position, double accel, double maxSpeed)
	:CMover(position,	24.0, CVector(0, 0),30, 1, 15, 25, 0.0, 0), animCount(0.0)
	, input(CControllerFactory::getIns().getController())
	, Accel(accel), MaxSpeed(maxSpeed), Direction(1) {

	if (CImageManager::getIns().find("player_komuk") == nullptr) {
		CImageManager::getIns().set("player_komuk", std::make_shared<CImage>("media/graphic/character/komuk/komuk.png", 16, 4, 4, 32, 32));
	}
}

void CMover_Player::Walk()
{
	CVector v = input->getVector() * Accel;
	if (v.x < 0) {
		if (Velocity.x > 0)Acceleration.x += v.x;
		else if(-Velocity.x < MaxSpeed)Acceleration.x += v.x;
	}else {
		if (Velocity.x < 0)Acceleration.x += v.x;
		else if (Velocity.x < MaxSpeed)Acceleration.x += v.x;
	}
	if (v.y < 0) {
		if (Velocity.y > 0)Acceleration.y += v.y;
		else if(-Velocity.y < MaxSpeed)Acceleration.y += v.y;
	}else {
		if (Velocity.y < 0)Acceleration.y += v.y;
		else if (Velocity.y < MaxSpeed)Acceleration.y += v.y;
	}
}

int CMover_Player::Update()
{
	if (input->update() > 0) {
		Direction = input->getDirection();
		animCount += 0.1;
		if (animCount > 3.0)animCount = 0.0;
	}
	else {
		animCount = 0.0;
	}
	Walk();
#ifdef _DEBUG
	printfDx("V:%lf,%lf\nA:%lf,%lf\n", Velocity.x, Velocity.y, Acceleration.x, Acceleration.y);
#endif
	return 0;
}

void CMover_Player::Render() const
{
	CImageManager::getIns().find("player_komuk")->DrawRota(Position.x, Position.y, 0.0, 1.0, Direction*4+std::round(animCount));
	//DrawCircleAA(Position.x, Position.y, Size, 32, 0xFF0000);
	DrawCircleAA(input->MouseX(), input->MouseY(), 16, 16, 0x00FFFF, 0, 2);
}

void CMover_Player::Dead()
{
}

void CMover_Player::Disappear()
{
}
