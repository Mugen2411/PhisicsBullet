#pragma once
#include <algorithm>
#include <fstream>
#include <memory>
#include <string>
#include <vector>

#include "CAttribute.h"
#include "CEnemySpawner.h"
#include "CVector.h"

class CField;

class CFieldHolder {
 public:
  CFieldHolder(std::string filepath);
  ~CFieldHolder();

  inline CField* GetFloor(unsigned int x, unsigned int y) {
    return floor_list_[width_ * y + x].get();
  }
  inline CField* GetWall(unsigned int x, unsigned int y) {
    return wall_list_[width_ * y + x].get();
  }

  void WriteFloor(CField* f, CVector pos);
  void WriteWall(CField* f, CVector pos);

  inline int GetWidth() { return width_; }
  inline int GetHeight() { return height_; }
  void Update();
  void Render() const;

  void ConvertSpawner(std::list<std::unique_ptr<CEnemySpawner>>& es,
                      CGameMediator* med, int level, CVector& playerPos);
  void ReadDefine();

  std::list<CVector> FindRoute(CVector start, CVector goal, CAttribute attrDEF,
                                int distance);  //先頭が一番自分に近い！
  std::vector<CVector> FindTargetByDistance(
      CVector start,
      int distance);  //基準となる座標から一定の距離離れた点のベクトルを返す
  inline int Index(int x, int y) { return y * width_ + x; }

  void Save();
  int Load();  // 0:正常 1:異常(失敗)
 protected:
  std::vector<std::unique_ptr<CField>> wall_list_;
  std::vector<std::unique_ptr<CField>> floor_list_;
  std::vector<std::vector<double>> g_, dist_;
  std::vector<std::vector<int>> diff_;
  std::vector<std::vector<CVector>> pre_;
  unsigned int width_, height_;
  std::string filepath_;

  void CheckDirection(std::vector<std::string> &bufF, std::vector<std::string> &bufW);
};
