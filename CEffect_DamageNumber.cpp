#include "CEffect_DamageNumber.h"
#include <DxLib.h>

CEffect_DamageNumber::CEffect_DamageNumber(CVector position, double num, int type, int Style)
	:CEffect(position), num(num), type(type), cnt(0), style(Style), dy(4.0), CND()
{
}

void CEffect_DamageNumber::Update()
{
	cnt++;
	Position.y -= dy;
	dy *= 0.83;
	if (cnt > 30)Status = 1;
}

void CEffect_DamageNumber::Render() const
{
	CND.Draw(Position.x, Position.y, num, type, style, style==0 ? 1.5 : 0.6);
}
