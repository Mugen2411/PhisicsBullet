#include "CMover_Shot_Festa_Superball.h"
#include "CImageManager.h"

CMover_Shot_Festa_Superball::CMover_Shot_Festa_Superball(double baseATK, CVector position, double angle)
	:CMover_ShotBase(baseATK, CAttribute(0.0).NONE(20), position, 12, CVector(angle)*16.0*(0.8+0.4*(GetRand(100)*0.01)), 0.5, COF(0.003, 0.15, 0.001, 1.0), 0)
	,color(0)
{
	color = GetRand(3);
	effectColor = effColor[color];
}

int CMover_Shot_Festa_Superball::Update()
{
	cnt++;
	if (cnt > 300)setStatus(STATUS::DEAD);
	if (Velocity.getLength2() < Constant::zero_border)setStatus(STATUS::DEAD);
	return Status;
}

void CMover_Shot_Festa_Superball::Render() const
{
	CImageManager::getIns().find("shot_festa_superball")->DrawRotaF(Position.x, Position.y, Velocity.getAngle(), 1.0, Constant::priority_shot, color);
}
