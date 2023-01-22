#pragma once
#include "CField.h"

class CField_Cave : public CField {
 public:
  CField_Cave(std::string gid, CVector position_);
  void Update();
  void Render() const;

  CField* Clone(CVector position_);

 private:
  int decoration_;
  double animation_cnt_;

  void Save(std::ofstream& fout);
};
