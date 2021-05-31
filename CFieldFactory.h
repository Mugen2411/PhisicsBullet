#pragma once
#include "CField.h"
#include <string>

class CFieldFactory
{
public:
	std::shared_ptr<CField> create(unsigned int x, unsigned int y, std::string name, std::vector<double> params);
};

