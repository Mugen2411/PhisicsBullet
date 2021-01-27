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
	
	void Draw(int x1, int y1, int num = 0);
	void Draw(float x1, float y1, int num = 0);
	void DrawRota(int x1, int y1, float angle, float extend, int num = 0);
	void DrawRotaF(float x1, float y1, float angle, float extend, int num = 0);
};

