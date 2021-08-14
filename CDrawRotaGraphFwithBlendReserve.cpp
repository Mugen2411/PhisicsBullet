#include "CDrawRotaGraphFwithBlendReserve.h"
#include <DxLib.h>

CDrawRotaGraphFwithBlendReserve::CDrawRotaGraphFwithBlendReserve(int GHandle, double Priority, float x, float y, float angle, float extend, int color, int Blendmode, int value)
:IRenderReserve(GHandle, Priority), x(x), y(y), angle(angle), extend(extend), Blendmode(Blendmode), value(value), Color(color){
}

void CDrawRotaGraphFwithBlendReserve::Render() const
{
	SetDrawBright((Color >> 16) & 0xFF, (Color >> 8) & 0xFF, (Color >> 0) & 0xFF);
	SetDrawBlendMode(Blendmode, value);
	DrawRotaGraphF(x, y, extend, angle, GHandle, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	SetDrawBright(0xFF, 0xFF, 0xFF);
}
