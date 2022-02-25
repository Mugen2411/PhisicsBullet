#include "CField_Wall_Log.h"
#include <DxLib.h>

CField_Wall_Log::CField_Wall_Log(std::string gid, CVector position, int state)
	:CField_Wall(gid, position, 0.0), animCount(0.0), state(state), BurningTime(600)
{
	FrictionCF = 1.6;
}

void CField_Wall_Log::Update()
{
	switch (state) {
	case 0:
		if (Temperature > 100)state = 1;
		break;
	case 1:
		animCount += 0.2;
		animCount = std::fmod(animCount, 3);
		BurningTime--;
		if (BurningTime < 0)state = 2;
		Damage = CAttribute(0.0).FIRE(4.0);
		break;
	case 2:
		Damage = CAttribute(0.0);
		break;
	}
}

void CField_Wall_Log::Render() const
{
	switch (state) {
	case 0:
	case 1:
		CImageManager::getIns().find("Field_Grass")->DrawRota(Position.x, Position.y, 0.0, 1.0, -1.0, 4);
		break;
	case 2:
		CImageManager::getIns().find("Field_Grass")->DrawRota(Position.x, Position.y, 0.0, 1.0, -1.0, 5);
		break;
	}
}

CField* CField_Wall_Log::Clone(CVector position)
{
	return new CField_Wall_Log(GID, position, state);
}

void CField_Wall_Log::Hit(CMover* m)
{
	if (state == 0)m->onWall(Position, Size, ReflectCF);
}
