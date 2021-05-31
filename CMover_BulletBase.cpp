#include "CMover_BulletBase.h"
#include "CImageManager.h"
#include <DxLib.h>

CMover_BulletBase::CMover_BulletBase(CVector position, CVector velocity)
	:CMover(MV_SHOT, position, 16, velocity, 0.5, 0, 0.7, 0.2, 0.92, 0)
{
}

/*int CMover_TestBullet::Update()
{
	if (Velocity.getLength2() < 0.01)Status = 2;
	if (Position.x<0 || Position.x>=Constant::ScreenW || Position.y<0 || Position.y>=Constant::ScreenH)Status = 2;
	return Status;
}*/
