#pragma once
#include "CField.h"

class CField_IceFloor : public CField {
 public:
  CField_IceFloor(std::string gid, CVector position_, double temperature, int direction);
  void Update();
  void Render() const;

  void AttributeReaction(CAttribute a) {
    auto f = a * CAttribute(0.0).Fire(1.0);
    temperature_ += f.Sum();
    f = a * CAttribute(0.0).Ice(1.0);
    temperature_ -= f.Sum();
    temperature_ = min(200, max(temperature_, -200));
  };

  CField* Clone(CVector position_);

  void Save(std::ofstream& fout);

 private:
  int direction_;
  int cnt_;
  const int kAnimDur;
};
