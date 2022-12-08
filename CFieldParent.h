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
	CGameMediator* med;
	std::unique_ptr<CFieldHolder> fieldHolder;
	
public:
	CFieldParent(CGameMediator*, std::string);
	~CFieldParent();
	void Update();
	void ApplyForceToMover(CMover* m);
	std::list<CVector> getRoute(CVector start, CVector goal, CAttribute attrDEF, int distance);
	std::vector<CVector> getTargetByDistance(CVector start, int distance);
	void Render()const;
	void convertSpawner(std::list<std::unique_ptr<CEnemySpawner>>& sp, int level, CVector &playerPos) {
		fieldHolder->convertSpawner(sp, med, level, playerPos);
	}
};

