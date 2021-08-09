#pragma once
#include "CAttribute.h"

class CCosutumeBase
{
public:
	CAttribute AttributeDEF;

	CAttribute getAttrDEF();
	int Update(double baseATK);
	void Render()const;
};

