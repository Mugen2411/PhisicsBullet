#pragma once
#include "CField.h"

class CField_IceFloor : public CField {
 public:
  CField_IceFloor(std::string gid, CVector position, double temperature);
  void Update();
  void Render() const;

  void attributeReaction(CAttribute a) {
    auto f = a * CAttribute(0.0).FIRE(1.0);
    Temperature += f.Sum();
    f = a * CAttribute(0.0).ICE(1.0);
    Temperature -= f.Sum();
    Temperature = min(200, max(Temperature, -200));
  };

  CField* Clone(CVector position);

  void Save(std::ofstream& fout);
};
