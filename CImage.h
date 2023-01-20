#pragma once
#include <vector>
#include <string>
#include <DxLib.h>

class CImage
{
private:
	std::vector<int> GHandle;
	std::string path;
	unsigned int ArrSize, Xnum, Ynum, Width, Height;
public:
	CImage(std::string path, int width, int height);
	CImage(std::string path, int AllNum, int Xnum, int Ynum, int w, int h);
	~CImage();

	void Release();
	inline void Load() {
		if (GHandle.empty()) {
			GHandle.resize(ArrSize);
			LoadDivGraph(path.c_str(), ArrSize, Xnum, Ynum, Width, Height, GHandle.data());
		}
	}
	
	void Draw(int x1, int y1, int priority = 0.0, int num = 0);
	void Draw(float x1, float y1, int priority = 0.0, int num = 0);
	void DrawRota(int x1, int y1, float angle, float extend, int priority = 0.0, int num = 0);
	void DrawRotaF(float x1, float y1, float angle, float extend, int priority = 0.0, int num = 0);
	void DrawRotaFwithBlend(float x1, float y1, float angle, float extend, int color, int Blendmode, int value, int priority = 0.0, int num = 0);
	void DrawRectwithBlend(int x1, int y1, int w1, int h1, int color, int Blendmode, int value, int priority = 0.0, int num = 0);
	void DrawExtendWithBlend(float x1, float y1, float x2, float y2, int color, int Blendmode, int value, int priority = 0.0, int num = 0);
	void DrawCircleGauge(int x, int y, double ratio, int priority = 0.0, int num = 0);
	void DrawModi(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, int priority = 0.0, int num = 0);
};

