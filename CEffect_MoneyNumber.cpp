#include "CEffect_MoneyNumber.h"
#include "CImageManager.h"
#include <cmath>

CEffect_MoneyNumber::CEffect_MoneyNumber(CVector position, int num)
:CEffect(position), num(num), dy(5.0), cnt(0){
}

void CEffect_MoneyNumber::Update()
{
	Position.y -= dy;
	dy *= 0.90;
	cnt++;
	if (cnt > 60)Status = 1;
}

void CEffect_MoneyNumber::Render() const
{
	int l = std::log10(num) + 1;
	int n = num;
	int x = Position.x + l * 5;
	for (int i = 0; i < l; i++) {
		CImageManager::getIns().find("effect_number3")->
			DrawRota(x, Position.y, 0.0, 1.0, Constant::priority_number, n % 10);
		x -= 10;
		n /= 10;
	}
	CImageManager::getIns().find("effect_number3")->
		DrawRota(x, Position.y, 0.0, 1.0, Constant::priority_number, 10);
}
