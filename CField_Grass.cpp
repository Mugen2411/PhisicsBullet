#include "CField_Grass.h"
#include <DxLib.h>

CField_Grass::CField_Grass(const char* gid, CVector position)
	:CField(gid, position,CVector(32.0,32.0),0.8,0, 1.0)
{
	if (CImageManager::getIns().find(GID) == nullptr) {
		CImageManager::getIns().set(GID, std::make_shared<CImage>("media/graphic/mapchip/grass.png", 4, 4, 1, 32, 32));
	}
}

void CField_Grass::Update()
{
}

void CField_Grass::Render()const
{
	CImageManager::getIns().find(GID)->DrawRota(Position.x, Position.y, 0.0, 1.0, 0);
	//DrawBox(Position.x - Size.x / 2, Position.y - Size.y / 2,
	//	Position.x + Size.x / 2, Position.y + Size.y / 2, 0x002000, TRUE);
}
