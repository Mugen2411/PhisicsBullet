#pragma once
#include "CField.h"

class CField_Dirt : public CField {
 public:
  CField_Dirt(std::string gid, CVector position_, int state_);
  void Update();
  void Render() const;

  CField* Clone(CVector position_);

 private:
  int state_;

  void Save(std::ofstream& fout);
};
