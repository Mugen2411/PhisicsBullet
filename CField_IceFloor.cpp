#include "CField_IceFloor.h"
#include <DxLib.h>

CField_IceFloor::CField_IceFloor(std::string gid, CVector position, double temperature)
	:CField(gid, position, CVector(32.0, 32.0), 0.3, temperature, 1.0, CAttribute(0,0,0,0,0,2.0))
{
}

void CField_IceFloor::Update()
{
}

void CField_IceFloor::Render()const
{
	CImageManager::getIns().find("Field_IceFloor")->DrawRota(Position.x, Position.y, 0.0, 1.0, -1.0, 0);
}
