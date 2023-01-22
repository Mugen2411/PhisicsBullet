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
      if (i->constants_.FrictionCF < min) min = i->constants_.FrictionCF;
      if (i->constants_.FrictionCF > max) max = i->constants_.FrictionCF;
    }
  }
  void GetMinMaxAirRes(double& min, double& max) {
    min = 9999;
    max = 0;
    for (auto& i : list_) {
      if (i->constants_.AirResCF < min) min = i->constants_.AirResCF;
      if (i->constants_.AirResCF > max) max = i->constants_.AirResCF;
    }
  }
  void GetMinMaxWaterRes(double& min, double& max) {
    min = 9999;
    max = 0;
    for (auto& i : list_) {
      if (i->constants_.WaterResCF < min) min = i->constants_.WaterResCF;
      if (i->constants_.WaterResCF > max) max = i->constants_.WaterResCF;
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
      if (i->accelaration_ < min) min = i->accelaration_;
      if (i->accelaration_ > max) max = i->accelaration_;
    }
  }

 private:
  std::vector<std::shared_ptr<CCostumeBase>> list_;
  void Register(CCostumeBase* f);
  int cx_;
  int cy_;
};