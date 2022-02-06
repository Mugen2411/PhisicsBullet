#pragma once
#include <vector>
#include <memory>
#include <algorithm>
#include <string>
#include <fstream>

class CField;

class CFieldHolder
{
protected:
	std::vector<std::shared_ptr<CField>> fieldlist;
	unsigned int width, height;
	std::string filePath;

public:
	CFieldHolder(std::string filepath);
	~CFieldHolder();

	std::shared_ptr<CField> getField(unsigned int x, unsigned int y);
	void write(std::shared_ptr<CField> f, unsigned int x, unsigned int y);
	int getWidth();
	int getHeight();
	void Update();
	void Render()const;

	void Save();
	int Load();		//0:³í 1:ˆÙí(¸”s)
};

