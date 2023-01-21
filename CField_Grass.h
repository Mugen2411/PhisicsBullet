#pragma once
#include "CField.h"
#include "CMover_BulletBase.h"
#include "CMover_ShotBase.h"

class CField_Grass : public CField {
  int decoration;
  double animCount;

  int state;
  int BurningTime;
  double Fertile;

 public:
  CField_Grass(std::string gid, CVector position);
  void Update();
  void Render() const;

  void attributeReaction(CAttribute a) {
    switch (state) {
      case 0: {
        auto f = a * CAttribute(0.0).FIRE(1.0);
        Temperature += f.Sum();
      } break;
      case 1: {
        auto aq_i = a * CAttribute(0.0).AQUA(1.0).ICE(1.5);
        Temperature -= aq_i.Sum();
      } break;
      case 2: {
        auto fl = a * CAttribute(0.0).FLOWER(1.0);
        Fertile += fl.Sum();
      } break;
    }
  };

  CField* Clone(CVector position);

  void Save(std::ofstream& fout);
};
