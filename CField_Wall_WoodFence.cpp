#include "CField_Wall_WoodFence.h"
#include "CImageManager.h"

CField_Wall_WoodFence::CField_Wall_WoodFence(std::string gid, CVector position, int state)
	:CField_Wall(gid, position, 0.0), state(state)
{
}

void CField_Wall_WoodFence::Update()
{
}

void CField_Wall_WoodFence::Render() const
{
	CImageManager::getIns().find("Field_Grass")->DrawRota(Position.x, Position.y, 0.0, 1.0, -1.0, 8 + state);
}
