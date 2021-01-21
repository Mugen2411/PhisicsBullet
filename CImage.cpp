#include "CImage.h"
#include <DxLib.h>

CImage::CImage(const char* path)
{
	GHandle.resize(1);

	GHandle.at(0) = LoadGraph(path);
}

CImage::CImage(const char* path, int AllNum, int Xnum, int Ynum, int w, int h)
{
	GHandle.resize(AllNum);

	LoadDivGraph(path, AllNum, Xnum, Ynum, w, h, GHandle.data());
}

CImage::~CImage()
{
}

void CImage::Draw(int x1, int y1, int num)
{
	if (num > GHandle.size())return;
	DrawGraph(x1, y1, GHandle[num], TRUE);
}

void CImage::Draw(float x1, float y1, int num)
{
	if (num > GHandle.size())return;
	DrawGraphF(x1, y1, GHandle[num], TRUE);
}

void CImage::DrawRota(float x1, float y1, float angle, float extend, int num)
{
	if (num > GHandle.size())return;
	DrawRotaGraphF(x1, y1, extend, angle, GHandle[num], TRUE);
}
