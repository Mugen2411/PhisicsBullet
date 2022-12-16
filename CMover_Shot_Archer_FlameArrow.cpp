#include "CMover_Shot_Archer_FlameArrow.h"
#include "CImageManager.h"

CMover_Shot_Archer_FlameArrow::CMover_Shot_Archer_FlameArrow(double baseATK, CVector position, double angle)
	:CMover_ShotBase(baseATK, CAttribute(0.0).NONE(30).FIRE(20), position, 18, CVector(angle) * 32.0, 0.2, COF(0.0, 0.5, 0.15, 0.0), 0xFF0000)
{
}

int CMover_Shot_Archer_FlameArrow::Update()
{
	if (Velocity.getLength2() < Constant::zero_border)setStatus(STATUS::DEAD);
	return Status;
}

void CMover_Shot_Archer_FlameArrow::Render() const
{
	CEffect_Bright::getIns().Register(CEffect_Bright::BrightDesc(Position, 96.0, 128));
	CImageManager::getIns().find("shot_archer_arrow")->DrawRotaF(Position.x, Position.y, Velocity.getAngle(), 1.0, Constant::priority_shot, 1);
}
