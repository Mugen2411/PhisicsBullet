#include "IRenderReserve.h"

#include <cmath>
#include <memory>

IRenderReserve::IRenderReserve(int GHandle, int Priority, double x, double y,
                               double w, double h)
    : GHandle(GHandle), Priority(Priority), x(x), y(y), w(w), h(h) {}

IRenderReserve::IRenderReserve(const IRenderReserve& v)
    : GHandle(v.GHandle),
      Priority(v.Priority),
      x(v.x),
      y(v.y),
      w(v.w),
      h(v.h) {}

bool compRR(const IRenderReserve* lhs, const IRenderReserve* rhs) {
  /*if (std::abs(lhs->x - rhs->x) <= (lhs->w + rhs->w) / 2 && std::abs(lhs->y -
  rhs->y) <= (lhs->h + rhs->h) / 2) { return lhs->Priority < rhs->Priority;
  }
  return (lhs->y + lhs->h / 2) < (rhs->y + rhs->h / 2);*/
  return lhs->Priority < rhs->Priority;
}