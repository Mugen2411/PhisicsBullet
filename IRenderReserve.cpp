#include "IRenderReserve.h"

#include <cmath>
#include <memory>

IRenderReserve::IRenderReserve(int GHandle, int Priority, double x, double y,
                               double w, double h)
    : graphic_handle_(GHandle), priority_(Priority), x_(x), y_(y), w_(w), h_(h) {}

IRenderReserve::IRenderReserve(const IRenderReserve& v)
    : graphic_handle_(v.graphic_handle_),
      priority_(v.priority_),
      x_(v.x_),
      y_(v.y_),
      w_(v.w_),
      h_(v.h_) {}

bool compRR(const IRenderReserve* lhs, const IRenderReserve* rhs) {
  /*if (std::abs(lhs->x_ - rhs->x_) <= (lhs->w_ + rhs->w_) / 2 && std::abs(lhs->y_ -
  rhs->y_) <= (lhs->h_ + rhs->h_) / 2) { return lhs->priority_ < rhs->priority_;
  }
  return (lhs->y_ + lhs->h_ / 2) < (rhs->y_ + rhs->h_ / 2);*/
  return lhs->priority_ < rhs->priority_;
}