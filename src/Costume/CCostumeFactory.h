#pragma once
#include <memory>
#include <string>
#include <vector>

#include "CCosutumeBase.h"

class CMover_Player;

class CCostumeFactory {
 public:
  CCostumeFactory();
  CCostumeBase* Create(std::string);
  CCostumeBase* Create(int);
  int GetSize() { return (int)list_.size(); }
  void GetMinMaxFriction(double& min, double& max) {
    min = 9999;
    max = 0;
    for (auto& i : list_) {
      if (i->cofs_.FrictionCF < min) min = i->cofs_.FrictionCF;
      if (i->cofs_.FrictionCF > max) max = i->cofs_.FrictionCF;
    }
  }
  void GetMinMaxAirRes(double& min, double& max) {
    min = 9999;
    max = 0;
    for (auto& i : list_) {
      if (i->cofs_.AirResCF < min) min = i->cofs_.AirResCF;
      if (i->cofs_.AirResCF > max) max = i->cofs_.AirResCF;
    }
  }
  void GetMinMaxWaterRes(double& min, double& max) {
    min = 9999;
    max = 0;
    for (auto& i : list_) {
      if (i->cofs_.WaterResCF < min) min = i->cofs_.WaterResCF;
      if (i->cofs_.WaterResCF > max) max = i->cofs_.WaterResCF;
    }
    min = 1.0 - max;
    max = 1.0 - min;
  }
  void GetMinMaxMass(double& min, double& max) {
    min = 9999;
    max = 0;
    for (auto& i : list_) {
      if (i->mass_ < min) min = i->mass_;
      if (i->mass_ > max) max = i->mass_;
    }
  }
  void GetMinMaxVelocity(double& min, double& max) {
    min = 9999;
    max = 0;
    for (auto& i : list_) {
      if (i->max_speed_ < min) min = i->max_speed_;
      if (i->max_speed_ > max) max = i->max_speed_;
    }
  }
  void GetMinMaxAccel(double& min, double& max) {
    min = 9999;
    max = 0;
    for (auto& i : list_) {
      if (i->accel_ < min) min = i->accel_;
      if (i->accel_ > max) max = i->accel_;
    }
  }

 private:
  std::vector<std::shared_ptr<CCostumeBase>> list_;
  void Register(CCostumeBase* f);
  int cx_;
  int cy_;
};