#pragma once
#include "CField.h"
#include "CNumberDrawer.h"

class CField_Wall_EnemySpawner : public CField {
 public:
  CField_Wall_EnemySpawner(std::string gid, CVector position_, int index);
  void Update();
  void Render() const;

  CField* Clone(CVector position_);

 private:
  int index_;
  CNumberDrawer number_drawer_;
};