#include "CMover_Player.h"
#include <DxLib.h>

CMover_Player::CMover_Player(CVector position, double accel, double maxSpeed) 
	:CMover(position,	24.0, CVector(0, 0),30, 1, 15, 25, 0.0, 0)
	,input(CControllerFactory::getIns().getController()), Accel(accel), MaxSpeed(maxSpeed) {
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
	input->update();
	Walk();
	printfDx(L"V:%lf,%lf\nA:%lf,%lf", Velocity.x, Velocity.y, Acceleration.x, Acceleration.y);
	return 0;
}

void CMover_Player::Render() const
{
	DrawCircleAA(Position.x, Position.y, Size, 32, 0xFF0000);
}

void CMover_Player::Dead()
{
}

void CMover_Player::Disappear()
{
}
