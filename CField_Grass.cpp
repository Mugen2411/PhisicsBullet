#include "CField_Grass.h"
#include <DxLib.h>

CField_Grass::CField_Grass(CFieldParent* f, CVector position)
	:CField(f,position,CVector(32.0,32.0),1.5,0, 1.0)
{
}

void CField_Grass::Update()
{
}

void CField_Grass::Render()const
{
	DrawBox(Position.x - Size.x / 2, Position.y - Size.y / 2,
		Position.x + Size.x / 2, Position.y + Size.y / 2, 0x002000, TRUE);
}
