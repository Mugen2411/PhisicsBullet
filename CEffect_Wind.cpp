#include "CEffect_Wind.h"
#include "CImageManager.h"
#include <DxLib.h>

CEffect_Wind::CEffect_Wind(CVector position, float power, float angle, float width, float length)
	:CEffect(position), basePos(position), duration(length / power / 0.25), power(power * 0.25), angle(angle), width(width), length(length),
	delta(GetRand(100) * 0.01 * Constant::PI2), x(0), y(0), z(0)
{

}

void CEffect_Wind::Update()
{
	if (cnt > duration) {
		Status = 1;
		return;
	}
	z = Constant::PI2 * Constant::perFrame * (duration / 4) * cnt;
	x = cos(z + delta) * width * 0.5;
	y = cnt * power;
	z = (sin(z + delta) + 1.0) * 0.5;
	Position.x = cos(angle) * y + cos(angle + Constant::PI / 2) * x;
	Position.y = sin(angle) * y + sin(angle + Constant::PI / 2) * x;
	Position += basePos;
	cnt++;
}

void CEffect_Wind::Render() const
{
	CImageManager::getIns().find("effect_wind")->DrawRotaFwithBlend(Position.x, Position.y,
		angle, ((double)(duration - cnt) / duration * 0.5 + 0.5) / 6.0,
		0xFFFFFF, CImageManager::BLENDMODE::BM_ALPHA, z * 0xFF,
		Constant::priority_effect, 1);
}
