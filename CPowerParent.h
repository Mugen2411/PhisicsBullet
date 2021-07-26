#pragma once
#include <memory>
#include <vector>
#include "CGameMediator.h"
#include "CMover.h"

class CPower;

class CPowerParent
{
protected:
	std::weak_ptr<CGameMediator> med;
	std::vector<std::shared_ptr<CPower>> powerList;
public:
	CPowerParent(std::shared_ptr<CGameMediator>);
	void Add(const std::shared_ptr<CPower>&);
	void ApplyForceToMover(CMover*);
	void Update();
	void Render();
};

