#include "CMover_Shot_Uniform_StrongMagic.h"
#include "CImageManager.h"

CMover_Shot_Uniform_StrongMagic::CMover_Shot_Uniform_StrongMagic(double baseATK, CVector position, double angle)
	:CMover_ShotBase(baseATK, CAttribute(0.0).NONE(200), position, 24, CVector(angle) * 6.0, 1.0, COF(0.0, 0.0, 0.0, 0.1), 0x00FFFF)
{
}

int CMover_Shot_Uniform_StrongMagic::Update()
{
	return Status;
}

void CMover_Shot_Uniform_StrongMagic::Render() const
{
	CImageManager::getIns().find("shot_uniform_strongmagic")->DrawRotaF(Position.x, Position.y, Velocity.getAngle(), 1, Constant::priority_shot);
}
