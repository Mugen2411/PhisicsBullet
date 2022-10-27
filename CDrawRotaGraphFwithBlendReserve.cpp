#include "CDrawRotaGraphFwithBlendReserve.h"
#include <DxLib.h>
#include <cmath>

CDrawRotaGraphFwithBlendReserve::CDrawRotaGraphFwithBlendReserve(int GHandle, double Priority, float x, float y, float angle, float extend, int color, int Blendmode, int value, int width, int height)
:IRenderReserve(GHandle, Priority, x, y, width* cos(angle)* extend + height * sin(angle) * extend, width* sin(angle)* extend + height * cos(angle) * extend), angle(angle), extend(extend), Blendmode(Blendmode), value(value), Color(color){
}

void CDrawRotaGraphFwithBlendReserve::Render() const
{
	SetDrawBright((Color >> 16) & 0xFF, (Color >> 8) & 0xFF, (Color >> 0) & 0xFF);
	SetDrawBlendMode(Blendmode, value);
	DrawRotaGraphF(x, y, extend, angle, GHandle, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	SetDrawBright(0xFF, 0xFF, 0xFF);
}
