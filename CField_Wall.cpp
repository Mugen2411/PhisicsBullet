#include "CField_Wall.h"
#include <DxLib.h>

CField_Wall::CField_Wall(std::string GID, CVector position, COF cofs)
	:CField(GID, position, CVector(32.0,32.0), cofs, 0.0, CAttribute(100.0), true)
{
}

bool CField_Wall::Hit(CMover* m)
{
	if (isWall) {
		m->FieldDispatch(this);
		return m->onWall(this, Cofs.ReflectCF);
	}
	return false;
}

