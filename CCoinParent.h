#pragma once
#include <memory>
#include <vector>

#include "CMover.h"
#include "CParts.h"

class CGameMediator;

class CCoinParent {
 public:
  CCoinParent(CGameMediator*);
  inline void RegisterCoin(std::shared_ptr<CMover> m) {
    reserve_list_.push_back(m);
  }
  void Update();
  void Render();

  void Hit(std::shared_ptr<CMover>);

 private:
  int cnt;
  CGameMediator* med_;
  std::vector<std::shared_ptr<CMover>> mover_list_;
  std::vector<std::shared_ptr<CMover>> reserve_list_;
};
