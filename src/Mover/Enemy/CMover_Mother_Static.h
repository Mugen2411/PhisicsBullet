#pragma once
#include "CEnemyFactory.h"
#include "CMover_Enemy.h"

class CMover_Mother_Static : public CMover_EnemyBase {
 public:
  struct MotherDesc {
    std::string gid;
    int max;
    int amount;
  };

  CMover_Mother_Static(CVector position, int Level, std::vector<MotherDesc> md,
                       int wait_time);

  int Update();
  void Render() const;

  CMover_EnemyBase* Clone(CVector position, int Level);

 protected:
  struct MotherState {
    int amount = 0;
  };
  CEnemyFactory CEF_;
  std::vector<MotherDesc> descList_;
  std::vector<MotherState> stateList_;
  int cnt_ = 0;
  int wait_time_;
  void ResetState();
};
