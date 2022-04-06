#include "CField_Wall_Vegetable.h"

CField_Wall_Vegetable::CField_Wall_Vegetable(std::string gid, CVector position, int col)
	:CField_Wall(gid, position, COF().setFrictionCF(0.0)),state(col)
{
	isWall = false;
}

void CField_Wall_Vegetable::Update()
{
}

void CField_Wall_Vegetable::Render() const
{
	CImageManager::getIns().find("Field_Grass")->DrawRota(Position.x, Position.y, 0.0, 1.0, Constant::priority_wall, 26+state);
}

CField* CField_Wall_Vegetable::Clone(CVector position)
{
	return new CField_Wall_Vegetable(GID, position, state);
}
