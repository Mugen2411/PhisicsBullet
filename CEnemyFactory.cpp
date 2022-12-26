#include "CEnemyFactory.h"
#include "CMover_Enemy_Bud.h"
#include "CMover_Enemy_Acecorn.h"
#include "CMover_Enemy_Shimaenaga.h"
#include "CMover_Enemy_Yadokari.h"
#include "CMover_Enemy_Goblin.h"
#include "CMover_Enemy_FlameSerpent.h"

CEnemyFactory::CEnemyFactory()
{
	Register("E_Budcorn", new CMover_Enemy_Bud(CVector(), 0));
	Register("E_Acecorn", new CMover_Enemy_Acecorn(CVector(), 0));
	Register("E_Shimaenaga", new CMover_Enemy_Shimaenaga(CVector(), 0));
	Register("E_Yadokari", new CMover_Enemy_Yadokari(CVector(), 0));
	Register("E_Goblin", new CMover_Enemy_Goblin(CVector(), 0));
	Register("E_FlameSerpent", new CMover_Enemy_FlameSerpent(CVector(), 0));
}

std::shared_ptr<CMover_EnemyBase> CEnemyFactory::create(std::string key, CVector position, int level)
{
	return std::shared_ptr<CMover_EnemyBase>(enemy_prototypes[key]->Clone(position, level));
}

void CEnemyFactory::Register(std::string key, CMover_EnemyBase* e)
{
	enemy_prototypes[key] = std::shared_ptr<CMover_EnemyBase>(e);
}
