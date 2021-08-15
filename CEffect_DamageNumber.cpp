#include "CEffect_DamageNumber.h"
#include <DxLib.h>

CEffect_Number::CEffect_Number(CVector position, double num, int type, int Style)
	:CEffect(position), num(num), type(type), cnt(0), style(Style), dy(4.0)
{
}

void CEffect_Number::Update()
{
	cnt++;
	Position.y -= dy;
	dy *= 0.90;
	if (cnt > 60)Status = 1;
}

void CEffect_Number::Render() const
{
	CNumberDrawer::getIns().Draw(Position.x, Position.y, num, type, style);
}
