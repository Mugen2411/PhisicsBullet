#include "CField_Dirt.h"
#include <DxLib.h>

CField_Dirt::CField_Dirt(std::string gid, CVector position)
	:CField(gid, position, CVector(32.0, 32.0), 0.9, 0, 1.0)
{
}

void CField_Dirt::Update()
{
}

void CField_Dirt::Render()const
{
	CImageManager::getIns().find("Field_Grass")->DrawRota(Position.x, Position.y, 0.0, 1.0, Constant::priority_field, 24);
}

CField* CField_Dirt::Clone(CVector position)
{
	return new CField_Dirt(GID, position);
}
