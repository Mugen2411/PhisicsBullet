#pragma once
#include "CVector.h"
#include "CEnemyFactory.h"
#include <memory>

class CGameMediator;

struct Spawner_Desc {
	std::string GID;
	int timeToSpawn = 0;
	int countOfSpawn = 0;
};

class CEnemySpawner {
	Spawner_Desc desc;
	CVector pos;
	CEnemyFactory CEF;
	std::weak_ptr<CGameMediator> mp;
	int level;

public:
	CEnemySpawner(std::weak_ptr<CGameMediator> mp, CVector pos, int level, Spawner_Desc desc);
	int Update();	//0:通常 1:スポーン終了(削除要請)
};