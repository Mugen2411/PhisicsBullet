#include "CMover_Shot_Festa_Cork.h"
#include "CImageManager.h"

CMover_Shot_Festa_Cork::CMover_Shot_Festa_Cork(double baseATK, CVector position, double angle)
	:CMover_ShotBase(baseATK, CAttribute(0.0).NONE(90), position, 16, CVector(angle)*16.0, 0.1, COF(0.001, 0.4, 0.1, 0.7), 0xFF7F00)
{
}

int CMover_Shot_Festa_Cork::Update()
{
	if (Velocity.getLength2() < Constant::zero_border)Status = 1;
	return Status;
}

void CMover_Shot_Festa_Cork::Render() const
{
	CImageManager::getIns().find("shot_festa_cork")->DrawRotaF(Position.x, Position.y, Velocity.getAngle(), 1.0, Constant::priority_shot);
}
