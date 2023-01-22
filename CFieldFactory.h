#pragma once
#include <algorithm>
#include <string>
#include <vector>

#include "CField.h"

class CFieldFactory {
 public:
  CFieldFactory();
  CField* create(int x, int y, std::string name);
  CField* create(CVector pos, std::string name);
  std::string getKey(int* n, int category_);

  void Render(int category_) const;

 private:
  void RegisterWall(CField* f);
  void RegisterFloor(CField* f);

  std::vector<std::unique_ptr<CField>> wall_prototypes_;
  std::vector<std::unique_ptr<CField>> floor_prototypes_;
  int fx_;
  int fy_;
  int wx_;
  int wy_;
};