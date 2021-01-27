#pragma once
#include <vector>
#include <memory>
#include <algorithm>

class CField;

class CFieldHolder
{
protected:
	std::vector<std::vector<std::shared_ptr<CField>>> fieldlist;

public:
	CFieldHolder(int w, int h);

	std::shared_ptr<CField> getField(int x, int y);
	void write(std::shared_ptr<CField> f, int x, int y);
	int getWidth();
	int getHeight();
	void Update();
	void Render()const;
};

