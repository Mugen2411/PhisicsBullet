#pragma once
#include <vector>
#include <memory>
#include <algorithm>

class CField;

class CFieldHolder
{
protected:
	std::vector<std::shared_ptr<CField>> fieldlist;
	unsigned int width, height;

public:
	CFieldHolder(unsigned int w, unsigned int h);

	std::shared_ptr<CField> getField(unsigned int x, unsigned int y);
	void write(std::shared_ptr<CField> f, unsigned int x, unsigned int y);
	unsigned int getWidth();
	unsigned int getHeight();
	void Update();
	void Render()const;
};

