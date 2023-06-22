#pragma once
#include <memory>
#include <string>
#include <unordered_map>

#include "CMover_Enemy.h"

class CEnemyFactory {
 private:
  std::unordered_map<std::string, std::shared_ptr<CMover_EnemyBase>>
      enemy_prototypes_;
  void Register(std::string, CMover_EnemyBase*);

 public:
  CEnemyFactory();
  std::shared_ptr<CMover_EnemyBase> Create(std::string key, CVector position_,
                                           int level);
};
