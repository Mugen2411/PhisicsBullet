#pragma once
#include <algorithm>
#include <list>
#include <memory>
#include <vector>

#include "Calc/Constant.h"
#include "Graphic/Draw/IRenderReserve.h"

class CRenderReserveList {
 public:
  inline static void Add(IRenderReserve* v) {
    if (v->x_ - v->w_ > Constant::kScreenW + 32 || v->x_ + v->w_ < -32 ||
        v->y_ - v->h_ > Constant::kScreenH + 32 || v->y_ + v->h_ < -32) {
      delete v;
      return;
    }
    list_.push_back(v);
  }
  static void Render();

 private:
  static std::list<IRenderReserve*> list_;
  friend IRenderReserve;
};