#pragma once
#include <DxLib.h>

#include <string>
#include <vector>

#include "CVector.h"

class CImage {
 public:
  CImage(std::string path, int width, int height);
  CImage(std::string path, int AllNum, int Xnum, int Ynum, int w, int h);
  ~CImage();

  void Release();
  inline void Load() {
    if (graphic_handle_.empty()) {
      graphic_handle_.resize(array_size_);
      LoadDivGraph(filepath_.c_str(), array_size_, x_num_, y_num_, width_, height_,
                   graphic_handle_.data());
    }
  }

  void Draw(int x1, int y1, int priority = 0.0, unsigned int num = 0);
  void Draw(double x1, double y1, int priority = 0.0, unsigned int num = 0);
  void Draw(CVector pos, int priority = 0.0, unsigned int num = 0);
  void DrawRota(int x1, int y1, float angle, float extend, int priority = 0.0,
                unsigned int num = 0);
  void DrawRota(CVector pos, float angle, float extend, int priority = 0.0,
                unsigned int num = 0);
  void DrawRotaF(double x1, double y1, float angle, float extend,
                 int priority = 0.0, unsigned int num = 0);
  void DrawRotaFwithBlend(double x1, double y1, float angle, float extend,
                          int color, int Blendmode, int value,
                          int priority = 0.0, unsigned int num = 0);
  void DrawRectwithBlend(int x1, int y1, int w1, int h1, int color,
                         int Blendmode, int value, int priority = 0.0,
                         unsigned int num = 0);
  void DrawExtendWithBlend(double x1, double y1, double x2, double y2,
                           int color, int Blendmode, int value,
                           int priority = 0.0, unsigned int num = 0);
  void DrawCircleGauge(int x, int y, double ratio, int priority = 0.0,
                       unsigned int num = 0);
  void DrawModi(double x1, double y1, double x2, double y2, double x3,
                double y3, double x4, double y4, int priority = 0.0,
                unsigned int num = 0);

 private:
  std::vector<int> graphic_handle_;
  std::string filepath_;
  unsigned int array_size_, x_num_, y_num_, width_, height_;
};
