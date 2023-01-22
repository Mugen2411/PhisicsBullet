#pragma once
#include <memory>
#include <vector>

#include "CMover.h"
#include "CParts.h"

class CGameMediator;

class CMoverParent {
 public:
  CMoverParent(CGameMediator*);
  inline void RegisterMover(std::shared_ptr<CMover> m) {
    reserve_list_.push_back(m);
  }
  std::weak_ptr<CMover> GetMover(int ID, int num);
  int GetCountByCategory(int ID);
  void Update();
  void Render();

  void Hit();

 private:
  int cnt;
  CGameMediator* med_;
  std::vector<std::shared_ptr<CMover>> mover_list_;
  std::vector<std::shared_ptr<CMover>> reserve_list_;
};
