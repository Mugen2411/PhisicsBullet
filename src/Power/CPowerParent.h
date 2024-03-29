#pragma once
#include <memory>
#include <vector>

#include "Scene/CGameMediator.h"
#include "Mover/CMover.h"

class CPower;

class CPowerParent {
 public:
  CPowerParent(CGameMediator*);
  void Add(const std::shared_ptr<CPower>&);
  void ApplyForceToMover(CMover*);
  void Update();
  void Render();

 protected:
  CGameMediator* med_;
  std::vector<std::shared_ptr<CPower>> power_list_;
};
