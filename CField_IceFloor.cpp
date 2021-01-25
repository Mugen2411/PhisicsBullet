#include "CField_IceFloor.h"
#include <DxLib.h>

CField_IceFloor::CField_IceFloor(CFieldParent* f, CVector position)
	:CField(f, "field_icefloor", position, CVector(32.0, 32.0), 0.3, 0, 1.0)
{
	if (CImageManager::getIns().find("field_icefloor") == nullptr) {
		CImageManager::getIns().set("field_icefloor", std::make_shared<CImage>("media/graphic/mapchip/ice.png", 2, 2, 1, 32, 32));
	}
}

void CField_IceFloor::Update()
{
}

void CField_IceFloor::Render()const
{
	CImageManager::getIns().find("field_icefloor")->DrawRota(Position.x, Position.y, 0.0, 1.0, 0);
	//DrawBox(Position.x - Size.x / 2, Position.y - Size.y / 2,
	//	Position.x + Size.x / 2, Position.y + Size.y / 2, 0x005060, TRUE);
}
