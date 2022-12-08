#include "CField_Wall_Tree.h"

CField_Wall_Tree::CField_Wall_Tree(std::string gid, CVector position)
	:CField_Wall(gid, position, COF().setReflectCF(0.9))
{
	Damage = CAttribute(12.0);
}

void CField_Wall_Tree::Update()
{
}

void CField_Wall_Tree::Render() const
{
	CImageManager::getIns().find("Field_Tree")->DrawRota(Position.x, Position.y-16, 0.0, 1.0, Constant::priority_wall, 0);
}

CField* CField_Wall_Tree::Clone(CVector position)
{
	return new CField_Wall_Tree(GID, position);
}
