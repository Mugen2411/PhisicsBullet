#include "CEnemySpawner.h"
#include "CGameMediator.h"

CEnemySpawner::CEnemySpawner(std::weak_ptr<CGameMediator> mp, CVector pos, int level, Spawner_Desc desc)
	:mp(mp), pos(pos), desc(desc) ,level(level), CEF() {
}

int CEnemySpawner::Update() {
	if (desc.timeToSpawn == 0) {
		for (int i = 0; i < desc.countOfSpawn; i++) {
			mp.lock()->RegisterMover(CEF.create(desc.GID, pos, level));
		}
		return 1;
	}
	--desc.timeToSpawn;
	return 0;
}