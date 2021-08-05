#include "CField_Wall_Tree.h"

CField_Wall_Tree::CField_Wall_Tree(std::string gid, CVector position)
	:CField_Wall(gid, position, 0.5)
{
}

void CField_Wall_Tree::Update()
{
}

void CField_Wall_Tree::Render() const
{
	CImageManager::getIns().find("Field_Grass")->DrawRota(Position.x, Position.y, 0.0, 1.0, -1.0, 3);
}
