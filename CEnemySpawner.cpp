#include "CEnemySpawner.h"

#include "CGameMediator.h"

CEnemySpawner::CEnemySpawner(CGameMediator* mp, CVector pos, int level,
                             SpawnerDesc desc)
    : med_ptr_(mp), pos_(pos), desc_(desc), level_(level), enemy_factory_() {}

int CEnemySpawner::Update() {
  if (desc_.time_to_spawn_ == 0) {
    if ((rand_() - (rand_.min)()) / (double)(rand_.max)() >
        desc_.spawn_probability_ * 0.01)
      return 1;
    for (int i = 0; i < desc_.count_of_spawn_; i++) {
      med_ptr_->RegisterMover(enemy_factory_.Create(desc_.gid, pos_, level_ + GetRand(2)));
    }
    return 1;
  }
  --desc_.time_to_spawn_;
  return 0;
}