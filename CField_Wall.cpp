#include "CField_Wall.h"
#include <DxLib.h>

CField_Wall::CField_Wall(CFieldParent* f, CVector position, double frictionCF, double temperature)
	:CField(f, "field_wall", position, CVector(32,32), frictionCF, temperature, 0.9)
{
	if (CImageManager::getIns().find("field_grass") == nullptr) {
		CImageManager::getIns().set("field_grass", std::make_shared<CImage>("media/graphic/mapchip/grass.png", 4, 4, 1, 32, 32));
	}
	if (CImageManager::getIns().find("field_icefloor") == nullptr) {
		CImageManager::getIns().set("field_icefloor", std::make_shared<CImage>("media/graphic/mapchip/ice.png", 2, 2, 1, 32, 32));
	}
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
	CImageManager::getIns().find("field_icefloor")->DrawRota(Position.x, Position.y, 0.0, 1.0, 1);
	//DrawBox(Position.x - Size.x / 2, Position.y - Size.y / 2,
	//	Position.x + Size.x / 2, Position.y + Size.y / 2, 0xFF0000, FALSE);
}

void CField_Wall::Hit(CMover* m)
{
	m->onWall(Position, Size, ReflectCF);
}

