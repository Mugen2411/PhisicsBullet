#include "CField_Wall.h"
#include <DxLib.h>

CField_Wall::CField_Wall(std::string GID, CVector position, double reflectCF)
	:CField(GID, position, CVector(32.0,32.0), 0.0, 0.0, reflectCF, CAttribute(0.0), true)
{
}

void CField_Wall::Hit(CMover* m)
{
	if(isWall)m->onWall(Position, Size, ReflectCF);
}

