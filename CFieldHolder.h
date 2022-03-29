#pragma once
#include "CVector.h"
#include "CAttribute.h"
#include <memory>
#include <algorithm>
#include <string>
#include <fstream>
#include <vector>

class CField;

class CFieldHolder
{
protected:
	std::vector<std::shared_ptr<CField>> walllist;
	std::vector<std::shared_ptr<CField>> floorlist;
	std::vector<double> dist;
	unsigned int width, height;
	std::string filePath;

public:
	CFieldHolder(std::string filepath);
	~CFieldHolder();

	std::shared_ptr<CField> getFloor(unsigned int x, unsigned int y);
	std::shared_ptr<CField> getWall(unsigned int x, unsigned int y);

	void writefloor(std::shared_ptr<CField> f, unsigned int x, unsigned int y);
	void writewall(std::shared_ptr<CField> f, unsigned int x, unsigned int y);

	int getWidth();
	int getHeight();
	void Update();
	void Render()const;

	std::vector<CVector> Find_Route(CVector start, CVector goal, CAttribute attrDEF);	//––”ö‚ªˆê”Ô©•ª‚É‹ß‚¢I
	int index(int, int);

	void Save();
	int Load();		//0:³í 1:ˆÙí(¸”s)
};

