#include "CField_Grass.h"
#include <DxLib.h>

CField_Grass::CField_Grass(std::string gid, CVector position)
	:CField(gid, position,CVector(32.0,32.0),0.8,0, 1.0)
{
	if (GetRand(3) != 0)decoration = 0;
	else {
		if (GetRand(1) == 0)decoration = 1;
		else decoration = 2;
	}
}

void CField_Grass::Update()
{
}

void CField_Grass::Render()const
{
	CImageManager::getIns().find("Field_Grass")->DrawRota(Position.x, Position.y, 0.0, 1.0, -1.1, decoration);
}

CField* CField_Grass::Clone(CVector position)
{
	return new CField_Grass(GID, position);
}
