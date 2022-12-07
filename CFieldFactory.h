#pragma once
#include "CField.h"
#include <string>
#include <vector>
#include <algorithm>

class CFieldFactory
{
private:
	std::vector<std::unique_ptr<CField>> wall_prototypes;
	std::vector<std::unique_ptr<CField>> floor_prototypes;
	void RegisterWall(CField* f);
	void RegisterFloor(CField* f);
	int fx;
	int fy;
	int wx;
	int wy;
public:
	CFieldFactory();
	CField* create(int x, int y, std::string name);
	std::string getKey(int *n, int category);

	void Render(int category)const;
};