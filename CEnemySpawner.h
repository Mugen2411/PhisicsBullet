#pragma once
#include "CVector.h"
#include "CEnemyFactory.h"
#include <memory>
#include <random>

class CGameMediator;

struct Spawner_Desc {
	std::string GID;
	int timeToSpawn = 0;
	int countOfSpawn = 0;
	int spawnProbability = 100;
};

class CEnemySpawner {
	Spawner_Desc desc;
	CVector pos;
	CEnemyFactory CEF;
	CGameMediator* mp;
	int level;
	std::random_device rand;
public:
	CEnemySpawner(CGameMediator* mp, CVector pos, int level, Spawner_Desc desc);
	int Update();	//0:通常 1:スポーン終了(削除要請)
};