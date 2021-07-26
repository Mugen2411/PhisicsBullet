#pragma once
#include "CField.h"
#include <string>

class CFieldFactory
{
public:
	std::shared_ptr<CField> create(int x, int y, std::string name);
};

