#include "CImage.h"
#include <algorithm>
#include <DxLib.h>
#include "CDrawGraphReserve.h"
#include "CDrawGraphFReserve.h"
#include "CDrawRotaGraphReserve.h"
#include "CDrawRotaGraphFReserve.h"
#include "CDrawRotaGraphFwithBlendReserve.h"
#include "CDrawModiWithBlend.h"
#include "CRenderReserveList.h"

CImage::CImage(std::string path):GHandle(0)
{
	GHandle.resize(1);

	*GHandle.data() = LoadGraph(path.c_str());
}

CImage::CImage(std::string path, int AllNum, int Xnum, int Ynum, int w, int h):GHandle(0)
{
	GHandle.resize(AllNum);

	LoadDivGraph(path.c_str(), AllNum, Xnum, Ynum, w, h, GHandle.data());
}

CImage::~CImage()
{
	std::for_each(GHandle.begin(), GHandle.end(), [](int v) { DeleteGraph(v); });
}

void CImage::Draw(int x1, int y1, double priority, int num)
{
	if (num > GHandle.size())return;
	CRenderReserveList::Add(new CDrawGraphReserve(GHandle[num] , x1, y1, priority));
}

void CImage::Draw(float x1, float y1, double priority, int num)
{
	if (num > GHandle.size())return;
	CRenderReserveList::Add(new CDrawGraphFReserve(GHandle[num], x1, y1, priority));
}

void CImage::DrawRota(int x1, int y1, float angle, float extend, double priority, int num)
{
	if (num > GHandle.size())return;
	CRenderReserveList::Add(new CDrawRotaGraphReserve(GHandle[num], priority, x1, y1, angle, extend));
}

void CImage::DrawRotaF(float x1, float y1, float angle, float extend, double priority, int num)
{
	if (num > GHandle.size())return;
	CRenderReserveList::Add(new CDrawRotaGraphFReserve(GHandle[num], priority, x1, y1, angle, extend));
}

void CImage::DrawRotaFwithBlend(float x1, float y1, float angle, float extend, int color, int Blendmode, int value, double priority, int num)
{
	if (num > GHandle.size())return;
	CRenderReserveList::Add(new CDrawRotaGraphFwithBlendReserve(GHandle[num], priority, x1, y1, angle, extend, color, Blendmode, value));
}

void CImage::DrawExtendWithBlend(float x1, float y1, float x2, float y2, int color, int Blendmode, int value, double priority, int num)
{
	if (num > GHandle.size())return;
	CRenderReserveList::Add(new CDrawExtendiWithBlendReserve(GHandle[num], priority, x1, y1, x2, y2, color, Blendmode, value));
}
