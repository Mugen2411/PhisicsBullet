#pragma once
#include <algorithm>
#include <fstream>
#include <memory>
#include <string>
#include <vector>

#include "Calc/CAttribute.h"
#include "Mover/Enemy/CEnemySpawner.h"
#include "Calc/CVector.h"

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

  void readStageData(std::list<std::unique_ptr<CEnemySpawner>>& es,
                      CGameMediator* med, int level, CVector& playerPos);

  std::list<CVector> FindRoute(CVector start, CVector goal, CAttribute attrDEF,
                                int distance);  //�擪����Ԏ����ɋ߂��I
  std::vector<CVector> FindTargetByDistance(
      CVector start,
      int distance);  //��ƂȂ���W������̋������ꂽ�_�̃x�N�g����Ԃ�
  inline int Index(int x, int y) { return y * width_ + x; }

  void Save();
  int Load();  // 0:���� 1:�ُ�(���s)
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
