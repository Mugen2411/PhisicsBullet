#pragma once
#include <memory>
#include <string>
#include <vector>

#include "CFieldHolder.h"
#include "CMover.h"
#include "CParts.h"

class CField;

class CFieldParent {
 public:
  CFieldParent(CGameMediator*, std::string);
  ~CFieldParent();
  void Update();
  void ApplyForceToMover(CMover* m);
  bool HitToMover(CMover* m);
  std::list<CVector> GetRoute(CVector start, CVector goal, CAttribute attrDEF,
                              int distance);
  std::vector<CVector> GetTargetByDistance(CVector start, int distance);
  void Render() const;
  void readStageData(std::list<std::unique_ptr<CEnemySpawner>>& sp, int level,
                      CVector& playerPos) {
    field_holder_->readStageData(sp, med_, level, playerPos);
  }

 private:
  CGameMediator* med_;
  std::unique_ptr<CFieldHolder> field_holder_;
};
