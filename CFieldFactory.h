#pragma once
#include "CField.h"
#include <string>
#include <list>
#include <algorithm>

class CFieldFactory
{
private:
	std::list<std::shared_ptr<CField>> prototypes;
	void Register(CField* f);

public:
	CFieldFactory();
	std::shared_ptr<CField> create(int x, int y, std::string name);
	std::string getKey(int *n);
};