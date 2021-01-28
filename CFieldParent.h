#pragma once
#include "CParts.h"
#include "CMover.h"
#include "CFieldHolder.h"
#include <memory>
#include <vector>

class CField;

class CFieldParent
{
	std::shared_ptr<CGameMediator> med;
	std::shared_ptr<CFieldHolder> fieldHolder;
	
public:
	CFieldParent(std::shared_ptr<CGameMediator>);
	void Update();
	void ApplyForceToMover(CMover* m);
	void Render()const;
};

