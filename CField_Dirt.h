#pragma once
#include "CField.h"

class CField_Dirt : public CField {
  int state;

 public:
  CField_Dirt(std::string gid, CVector position, int state);
  void Update();
  void Render() const;

  CField* Clone(CVector position);

  void Save(std::ofstream& fout);
};
