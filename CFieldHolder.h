#pragma once
#include "CVector.h"
#include "CAttribute.h"
#include <memory>
#include <algorithm>
#include <string>
#include <fstream>
#include <vector>
#include "CEnemySpawner.h"

class CField;

class CFieldHolder
{
protected:
	std::vector<std::unique_ptr<CField>> walllist;
	std::vector<std::unique_ptr<CField>> floorlist;
	std::vector<std::vector<double>> g, dist;
	std::vector<std::vector<int>> diff;
	std::vector<std::vector<CVector>> pre;
	unsigned int width, height;
	std::string filePath;

public:
	CFieldHolder(std::string filepath);
	~CFieldHolder();

	inline CField* getFloor(unsigned int x, unsigned int y) {
		return floorlist[width * y + x].get();
	}
	inline CField* getWall(unsigned int x, unsigned int y) {
		return walllist[width * y + x].get();
	}

	void writefloor(CField* f, unsigned int x, unsigned int y);
	void writewall(CField* f, unsigned int x, unsigned int y);

	inline int getWidth() {
		return width;
	}
	inline int getHeight() {
		return height;
	}
	void Update();
	void Render()const;

	void convertSpawner(std::list<std::unique_ptr<CEnemySpawner>>& es, CGameMediator* med, int level, CVector &playerPos);
	void readDefine();

	std::list<CVector> Find_Route(CVector start, CVector goal, CAttribute attrDEF, int distance);	//先頭が一番自分に近い！
	std::vector<CVector> findTargetByDistance(CVector start, int distance);		//基準となる座標から一定の距離離れた点のベクトルを返す
	inline int index(int x, int y) {
		return y * width + x;
	}

	void Save();
	int Load();		//0:正常 1:異常(失敗)
};

