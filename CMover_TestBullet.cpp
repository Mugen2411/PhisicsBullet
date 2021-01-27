#include "CMover_TestBullet.h"
#include "CImageManager.h"
#include <DxLib.h>

CMover_TestBullet::CMover_TestBullet(CVector position, CVector velocity)
	:CMover(position, 16, velocity, 0.5, 0, 0.7, 0.2, 0.92, 0)
{
	if (CImageManager::getIns().find("bullet_arrow") == nullptr) {
		CImageManager::getIns().set("bullet_arrow", std::make_shared<CImage>("media/graphic/character/noa/arrow.png"));
	}
}

int CMover_TestBullet::Update()
{
	if (Velocity.getLength2() < 0.01)Status = 2;
	if (Position.x<0 || Position.x>=Constant::ScreenW || Position.y<0 || Position.y>=Constant::ScreenH)Status = 2;
	return Status;
}

void CMover_TestBullet::Render() const
{
	CImageManager::getIns().find("bullet_arrow")->DrawRota(Position.x, Position.y, Velocity.getAngle(), 1.0);
	//DrawCircleAA(Position.x, Position.y, Size, 12, 0xFFFFFF);
}

void CMover_TestBullet::Dead()
{
}

void CMover_TestBullet::Disappear()
{
}

void CMover_TestBullet::ifonWall()
{
	//Status = 2;
}


