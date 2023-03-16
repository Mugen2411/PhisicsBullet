#pragma once
#include "CField.h"

class CField_Lava : public CField {
 public:
  CField_Lava(std::string gid, CVector position_, double temperature, int direction);
  void Update();
  void Render() const;

  void AttributeReaction(CAttribute a) {
    auto f = a * CAttribute(0.0).Fire(1.0);
    temperature_ += f.Sum();
    f = a * CAttribute(0.0).Aqua(0.5).Ice(1.0);
    temperature_ -= f.Sum();
    temperature_ = min(1000, max(temperature_, -100));
  };

  CField* Clone(CVector position_);

 private:
  int cnt_;
  int kAnimDur;
  int direction_;
};
