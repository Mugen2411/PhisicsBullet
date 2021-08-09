#include "CEffect_DamageNumber.h"
#include <DxLib.h>

CEffect_DamageNumber::CEffect_DamageNumber(CVector position, double num, int type)
	:CEffect(position), num(num), type(type), cnt(0)
{
}

void CEffect_DamageNumber::Update()
{
	Position.y -= 1;
	cnt++;
	if (cnt > 30)Status = 1;
}

void CEffect_DamageNumber::Render() const
{
	//printfDx("x:%d, y:%d, num:%d, type:%d\n", Position.x, Position.y, num, type);
	CNumberDrawer::getIns().Draw(Position.x, Position.y, num, type);
}
