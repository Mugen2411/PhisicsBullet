#include "CEnemySpawner.h"

#include "CDataLoader.h"
#include "CGameMediator.h"
#include "CMover_Mother_Static.h"
#include "CPassiveSkill.h"

CEnemySpawner::CEnemySpawner(CGameMediator* mp, CVector pos, int level,
                             SpawnerDesc desc)
    : med_ptr_(mp), pos_(pos), desc_(desc), level_(level), enemy_factory_() {}

int CEnemySpawner::Update() {
  if (desc_.time_to_spawn_ == 0) {
    if ((rand_() - (rand_.min)()) / (double)(rand_.max)() >
        desc_.spawn_probability_ * 0.01)
      return 1;
    if (desc_.gid[0] == 'E') {
      int am = CPassiveSkill::GetIns().GetEnemyAmount(desc_.count_of_spawn_);
      for (int i = 0; i < am; i++) {
        med_ptr_->RegisterMover(enemy_factory_.Create(
            desc_.gid, pos_,
            level_ + GetRand(2) + CPassiveSkill::GetIns().GetEnemyLevelAdd()));
      }
    } else {
      std::vector<CMover_Mother_Static::MotherDesc> mdList;
      auto c = CDataLoader::GetIns().Get("stage")->GetChild("spawn");
      auto d = c->GetChild(std::to_string(desc_.index))->GetChild("child");
      int i = 0;
      while (1) {
        CMover_Mother_Static::MotherDesc tmpMD;
        auto t = d->GetChild(std::to_string(i));
        if (t == nullptr) break;
        tmpMD.gid = t->GetChild("gid")->GetString();
        tmpMD.amount = CPassiveSkill::GetIns().GetEnemyAmount(t->GetChild("amount")->GetInt());
        mdList.push_back(tmpMD);
        i++;
      }
      med_ptr_->RegisterMover(std::make_shared<CMover_Mother_Static>(
          pos_, level_, mdList,
          c->GetChild(std::to_string(desc_.index))
              ->GetChild("wait")
              ->GetInt()));
    }
    return 1;
  }
  --desc_.time_to_spawn_;
  return 0;
}