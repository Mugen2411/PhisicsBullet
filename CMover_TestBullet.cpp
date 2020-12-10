#include "CMover_TestBullet.h"
#include <DxLib.h>

CMover_TestBullet::CMover_TestBullet(CVector position, CVector velocity)
	:CMover(position, 8, velocity, 0.03, 0, 0.7, 3, 0.8, 0.8)
{
}

int CMover_TestBullet::Update()
{
	if (Velocity.getLength2() < 0.05)Status = 2;
	if (Position.x<0 || Position.x>=Constant::ScreenW || Position.y<0 || Position.y>=Constant::ScreenH)Status = 2;
	return Status;
}

void CMover_TestBullet::Render() const
{
	DrawCircleAA(Position.x, Position.y, Size, 12, 0xFFFFFF);
}

void CMover_TestBullet::Dead()
{
}

void CMover_TestBullet::Disappear()
{
}