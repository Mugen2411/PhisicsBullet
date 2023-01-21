#pragma once
#include <memory>
#include <vector>

#include "CEffect.h"

class CEffectParent {
  static std::vector<std::shared_ptr<CEffect>> effectlist;

 public:
  static void RegisterEffect(std::shared_ptr<CEffect> e);
  static void Reset();
  static void Update();
  static void Render();
  static bool empty();
};
