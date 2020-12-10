#pragma once
#include <memory>
#include <vector>

class CPower;

class CPowerParent
{
protected:
	std::vector<std::shared_ptr<CPower>> powerList;
public:
	CPowerParent();
	void Add(std::shared_ptr<CPower>);
	void Update();
	void Render();
};

