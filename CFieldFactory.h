#pragma once
#include "CField.h"
#include <string>
#include <vector>
#include <algorithm>

class CFieldFactory
{
private:
	std::vector<std::shared_ptr<CField>> prototypes;
	void Register(CField* f);

public:
	CFieldFactory();
	std::shared_ptr<CField> create(int x, int y, std::string name);
	std::string getKey(int *n);
};