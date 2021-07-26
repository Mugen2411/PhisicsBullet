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
	std::weak_ptr<CGameMediator> med;
	std::shared_ptr<CFieldHolder> floorHolder;
	
public:
	CFieldParent(std::shared_ptr<CGameMediator>, std::string);
	~CFieldParent();
	void Update();
	void ApplyForceToMover(CMover* m);
	void Render()const;
};

