#pragma once
#include "CParts.h"
#include "CMover.h"
#include "CFieldHolder.h"
#include <memory>
#include <vector>
#include <string>

class CField;

class CFieldParent
{
	std::shared_ptr<CGameMediator> med;
	std::shared_ptr<CFieldHolder> floorHolder;
	std::shared_ptr<CFieldHolder> wallHolder;
	
public:
	CFieldParent(std::shared_ptr<CGameMediator>, int, int);
	void Update();
	void ApplyForceToMover(CMover* m);
	void Render()const;
};

