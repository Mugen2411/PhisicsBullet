#include "CField_Wall_DeepWater.h"

CField_Wall_DeepWater::CField_Wall_DeepWater(std::string gid, CVector position)
	:CField_Wall(gid, position, COF())
{
	Damage = CAttribute(12.0);
}

void CField_Wall_DeepWater::Update()
{
}

void CField_Wall_DeepWater::Render() const
{
	CImageManager::getIns().find("Field_IceFloor")->DrawRota(Position.x, Position.y, 0, 1, Constant::priority_wall, 2);
}

CField* CField_Wall_DeepWater::Clone(CVector position)
{
	return new CField_Wall_DeepWater(GID, position);
}
