#include "CMover_Player.h"
#include "CImageManager.h"
#include <cmath>
#include <DxLib.h>
#include "CMover_Shot_Uniform_Homing.h"

CMover_Player::CMover_Player(CVector position, double accel, double maxSpeed)
	:CMover(MV_PLAYER, position,	24.0, CVector(0.0, 0.0),30, 1, 15, 25, 0.0, 0), animCount(0.0)
	, input(CControllerFactory::getIns().getController())
	, Accel(accel), MaxSpeed(maxSpeed), Direction(1), State(0) ,baseParams(0){
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
	if (input->LClick(true) % 20 == 1) {
		med.lock()->RegisterMover(std::make_shared<CMover_Shot_Uniform_Homing>(baseParams, Position, input->getMouseAngle(Position)));
	}
	Walk();
	
#ifdef _DEBUG
	printfDx("V:%lf,%lf\nA:%lf,%lf\n", Velocity.x, Velocity.y, Acceleration.x, Acceleration.y);
#endif
	return 0;
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

void CMover_Player::Dispatch(std::shared_ptr<CMover> m)
{
	m->Hit(this);
}

