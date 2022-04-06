#include "CField_IceFloor.h"
#include <DxLib.h>

CField_IceFloor::CField_IceFloor(std::string gid, CVector position, double temperature)
	:CField(gid, position, CVector(32.0, 32.0), COF().setFrictionCF(0.1), temperature, CAttribute(0.0).ICE(2.0))
{
}

void CField_IceFloor::Update()
{
	if (Temperature < 0) {
		Cofs.setWaterResCF(0.0);
		Damage = CAttribute(0.0).ICE(2.0);
	}
	else {
		Cofs.setWaterResCF(0.7);
		Damage = CAttribute(0.0).AQUA(0.5);
	}
}

void CField_IceFloor::Render()const
{
	if(Temperature < 0)CImageManager::getIns().find("Field_IceFloor")->DrawRota(Position.x, Position.y, 0.0, 1.0, Constant::priority_field, 0);
	else CImageManager::getIns().find("Field_IceFloor")->DrawRota(Position.x, Position.y, 0.0, 1.0, Constant::priority_field, 1);
}

CField* CField_IceFloor::Clone(CVector position)
{
	return new CField_IceFloor(GID,position, Temperature);
}
