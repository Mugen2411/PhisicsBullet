#include "CField_Wall_Cave.h"
#include "CImageManager.h"

CField_Wall_Cave::CField_Wall_Cave(std::string gid, CVector position, int state)
	:CField_Wall(gid, position, COF().setReflectCF(0.9)), state(state)
{
	Damage = CAttribute(12.0);
}

void CField_Wall_Cave::Update()
{
}

void CField_Wall_Cave::Render() const
{
	CImageManager::getIns().find("Field_Cave")->DrawRota(Position.x, Position.y, 0.0, 1.0, Constant::priority_wall, 8 + state);
}

CField* CField_Wall_Cave::Clone(CVector position)
{
	return new CField_Wall_Cave(GID, position, state);
}
