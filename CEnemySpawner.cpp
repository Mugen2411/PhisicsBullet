#include "CEnemySpawner.h"
#include "CGameMediator.h"

CEnemySpawner::CEnemySpawner(CGameMediator* mp, CVector pos, int level, Spawner_Desc desc)
	:mp(mp), pos(pos), desc(desc) ,level(level), CEF() {
}

int CEnemySpawner::Update() {
	if (desc.timeToSpawn == 0) {
		if ((rand() - (rand.min)()) / (double)(rand.max)() > desc.spawnProbability * 0.01)return 1;
		for (int i = 0; i < desc.countOfSpawn; i++) {
			mp->RegisterMover(CEF.create(desc.GID, pos, level+GetRand(2)));
		}
		return 1;
	}
	--desc.timeToSpawn;
	return 0;
}