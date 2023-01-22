#pragma once
#include <memory>
#include <random>

#include "CEnemyFactory.h"
#include "CVector.h"

class CGameMediator;

struct SpawnerDesc {
  SpawnerDesc()
      : gid(), time_to_spawn_(0), count_of_spawn_(0), spawn_probability_(100) {}

  std::string gid;
  int time_to_spawn_ = 0;
  int count_of_spawn_ = 0;
  int spawn_probability_ = 100;
};

class CEnemySpawner {
 public:
  CEnemySpawner(CGameMediator* mp, CVector pos, int level, SpawnerDesc desc);
  int Update();  // 0:通常 1:スポーン終了(削除要請)

 private:
  SpawnerDesc desc_;
  CVector pos_;
  CEnemyFactory enemy_factory_;
  CGameMediator* med_ptr_;
  int level_;
  std::random_device rand_;
};