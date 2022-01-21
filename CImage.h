#pragma once
#include <vector>
#include <string>

class CImage
{
private:
	std::vector<int> GHandle;
public:
	CImage(std::string path);
	CImage(std::string path, int AllNum, int Xnum, int Ynum, int w, int h);
	~CImage();
	
	void Draw(int x1, int y1, double priority = 0.0, int num = 0);
	void Draw(float x1, float y1, double priority = 0.0, int num = 0);
	void DrawRota(int x1, int y1, float angle, float extend, double priority = 0.0, int num = 0);
	void DrawRotaF(float x1, float y1, float angle, float extend, double priority = 0.0, int num = 0);
	void DrawRotaFwithBlend(float x1, float y1, float angle, float extend, int color, int Blendmode, int value, double priority = 0.0, int num = 0);
	void DrawExtendWithBlend(float x1, float y1, float x2, float y2, int color, int Blendmode, int value, double priority = 0.0, int num = 0);
	void DrawCircleGauge(int x, int y, double ratio, double priority = 0.0, int num = 0);
	//void DrawOnCamela(int x, int y, int num = 0);		//ƒJƒƒ‰À•W‚ğŒ³‚É•`‰æ‚·‚éŠÖ”‘½•ª—v‚é‚æ‚Ë
};

