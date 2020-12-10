#include "CField_Wall.h"
#include <DxLib.h>

CField_Wall::CField_Wall(CFieldParent* f, CVector position, double frictionCF, double temperature)
	:CField(f, position, CVector(32,32), frictionCF, temperature, 1.0)
{
}

void CField_Wall::setFrictionForce(CMover* m)
{
	m->ApplyFrictionForce(FrictionCF);
	m->onWall(Position, Size, ReflectCF);
}

void CField_Wall::Update()
{
}

void CField_Wall::Render() const
{
	DrawBox(Position.x - Size.x / 2, Position.y - Size.y / 2,
		Position.x + Size.x / 2, Position.y + Size.y / 2, 0xFF0000, FALSE);
}

void CField_Wall::Hit(CMover* m)
{
	m->onWall(Position, Size, ReflectCF);
}

