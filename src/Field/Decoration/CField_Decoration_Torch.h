#pragma once
#include "Field/Wall/CField_Wall.h"
#include "Mover/Bullet/CMover_BulletBase.h"
#include "Mover/Shot/CMover_ShotBase.h"

class CField_Decoration_Torch : public CField_Wall {
 public:
  CField_Decoration_Torch(std::string gid, CVector position_);

  void Update();
  void Render() const;

  void AttributeReaction(CAttribute a) {
    auto f = a * CAttribute(0.0).Fire(1.0);
    if (f.Sum() > 0.0) {
      state_ = 1;
    }
    auto aq = a * CAttribute(0.0).Aqua(1.0);
    if (aq.Sum() > 0.0) {
      state_ = 0;
    }
  };
  virtual void AttributeEffect(CMover_BulletBase* m){};

 private:
  double animation_cnt_;
  int state_;
  int burning_time_;

  CField* Clone(CVector position_);
};
