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
	std::shared_ptr<CFieldHolder> fieldHolder;
	
public:
	CFieldParent(std::shared_ptr<CGameMediator>, std::string);
	~CFieldParent();
	void Update();
	void ApplyForceToMover(CMover* m);
	std::vector<CVector> getRoute(CVector start, CVector goal, CAttribute attrDEF);
	void Render()const;
	void convertEnemySpawner(std::list<std::unique_ptr<CEnemySpawner>>& sp, int level) {
		fieldHolder->convertEnemySpawner(sp, med, level);
	}
};

