#include "CField_Error.h"
#include "CImageManager.h"

CField_Error::CField_Error(std::string gid, CVector position):CField(gid, position, CVector(32, 32), COF(), 0,  CAttribute(0.0))
{
}

void CField_Error::Update()
{
}

void CField_Error::Render() const
{
	CImageManager::getIns().find("Field_Error")->DrawRota(Position.x, Position.y, 0.0, 1.0, -1.0);
}

CField* CField_Error::Clone(CVector position)
{
	return new CField_Error(GID, position);
}
