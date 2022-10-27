#include "CDrawModiWithBlend.h"
#include <DxLib.h>
#include <cmath>

CDrawExtendiWithBlendReserve::CDrawExtendiWithBlendReserve(int GHandle, double Priority, float x1, float y1, float x2, float y2, int color, int Blendmode, int value)
:IRenderReserve(GHandle, Priority, x1, y1, std::abs(x1-x2), std::abs(y1-y2)), x1(x1), y1(y1), x2(x2), y2(y2), Blendmode(Blendmode), value(value), Color(color) {
}

void CDrawExtendiWithBlendReserve::Render() const
{
	SetDrawBright((Color >> 16) & 0xFF, (Color >> 8) & 0xFF, (Color >> 0) & 0xFF);
	SetDrawBlendMode(Blendmode, value);
	DrawExtendGraphF(x1, y1, x2, y2, GHandle, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	SetDrawBright(0xFF, 0xFF, 0xFF);
}
