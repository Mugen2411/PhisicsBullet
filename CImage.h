#pragma once
#include <vector>

class CImage
{
private:
	std::vector<int> GHandle;
public:
	CImage(const char* path);
	CImage(const char* path, int AllNum, int Xnum, int Ynum, int w, int h);
	~CImage();
	
	void Draw(int x1, int y1, double priority = 0.0, int num = 0);
	void Draw(float x1, float y1, double priority = 0.0, int num = 0);
	void DrawRota(int x1, int y1, float angle, float extend, double priority = 0.0, int num = 0);
	void DrawRotaF(float x1, float y1, float angle, float extend, double priority = 0.0, int num = 0);
	void DrawRotaFwithBlend(float x1, float y1, float angle, float extend, int color, int Blendmode, int value, double priority = 0.0, int num = 0);

	//void DrawOnCamela(int x, int y, int num = 0);		//�J�������W�����ɕ`�悷��֐������v����
};

