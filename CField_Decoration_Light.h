#pragma once
#include "CField_Wall.h"
#include "CMover_BulletBase.h"
#include "CMover_ShotBase.h"

class CField_Decoration_Light : public CField_Wall {
 public:
  CField_Decoration_Light(std::string gid, CVector position_);

  void Update();
  void Render() const;

  void AttributeReaction(CAttribute a) {
    auto f = a * CAttribute(0.0).Thunder(1.0);
    if (f.Sum() > 0.0) {
      state_ = 1;
    }
  };
  virtual void AttributeEffect(CMover_BulletBase* m){};

  private:
  int state_;

  CField* Clone(CVector position_);
};
