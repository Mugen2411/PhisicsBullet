#pragma once
#include <unordered_map>
#include <memory>
#include <string>
#include "CMover_Enemy.h"

class CEnemyFactory
{
private:
	std::unordered_map<std::string ,std::shared_ptr<CMover_EnemyBase>> enemy_prototypes;
	void Register(std::string, CMover_EnemyBase*);
public:
	CEnemyFactory();
	std::shared_ptr<CMover_EnemyBase> create(std::string key, CVector position, int level);
};

