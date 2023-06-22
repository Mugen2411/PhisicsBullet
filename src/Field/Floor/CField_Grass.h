#pragma once
#include "Field/CField.h"
#include "Mover/Bullet/CMover_BulletBase.h"
#include "Mover/Shot/CMover_ShotBase.h"

class CField_Grass : public CField {
 public:
  CField_Grass(std::string gid, CVector position_);
  void Update();
  void Render() const;

  void AttributeReaction(CAttribute a) {
    switch (state_) {
      case 0: {
        auto f = a * CAttribute(0.0).Fire(1.0);
        temperature_ += f.Sum();
      } break;
      case 1: {
        auto aq_i = a * CAttribute(0.0).Aqua(1.0).Ice(1.5);
        temperature_ -= aq_i.Sum();
      } break;
      case 2: {
        auto fl = a * CAttribute(0.0).Flower(1.0);
        fertile_ += fl.Sum();
      } break;
    }
  };

  CField* Clone(CVector position_);

 private:
  int decoration_;
  double animation_cnt_;

  int state_;
  int burning_time_;
  double fertile_;
};
