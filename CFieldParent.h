#pragma once
#include "CParts.h"
#include "CMover.h"
#include <memory>
#include <vector>
#include <algorithm>

class CField;

class CFieldParent
{
	std::vector<std::vector<std::shared_ptr<CField>>> fieldlist;
	
public:
	CFieldParent(CGameMediator*);
	void Update();
	void ApplyForceToMover(CMover* m);
	void Render()const;
};

