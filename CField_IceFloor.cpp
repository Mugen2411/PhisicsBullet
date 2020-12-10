#include "CField_IceFloor.h"
#include <DxLib.h>

CField_IceFloor::CField_IceFloor(CFieldParent* f, CVector position)
	:CField(f, position, CVector(32.0, 32.0), 0.3, 0, 1.0)
{
}

void CField_IceFloor::Update()
{
}

void CField_IceFloor::Render()const
{
	DrawBox(Position.x - Size.x / 2, Position.y - Size.y / 2,
		Position.x + Size.x / 2, Position.y + Size.y / 2, 0x005060, TRUE);
}
