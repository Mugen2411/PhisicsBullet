#include "CField_IceFloor.h"
#include <DxLib.h>

CField_IceFloor::CField_IceFloor(const char* gid, CVector position, double temperature)
	:CField(gid, position, CVector(32.0, 32.0), 0.3, temperature, 1.0)
{
	if (CImageManager::getIns().find(GID) == nullptr) {
		CImageManager::getIns().set(GID, std::make_shared<CImage>("media/graphic/mapchip/ice.png", 2, 2, 1, 32, 32));
	}
}

void CField_IceFloor::Update()
{
}

void CField_IceFloor::Render()const
{
	CImageManager::getIns().find(GID)->DrawRota(Position.x, Position.y, 0.0, 1.0, 0);
	//DrawBox(Position.x - Size.x / 2, Position.y - Size.y / 2,
	//	Position.x + Size.x / 2, Position.y + Size.y / 2, 0x005060, TRUE);
}
