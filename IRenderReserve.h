#pragma once
#include <memory>

class CRenderReserveList;

class IRenderReserve {
 protected:
  const int GHandle;
  const int Priority;
  const double x, y, w, h;

 public:
  IRenderReserve(int GHandle, int Priority, double x, double y, double w,
                 double h);
  virtual ~IRenderReserve() {}
  IRenderReserve(const IRenderReserve& v);

  virtual void Render() const = 0;
  /*bool operator<(const IRenderReserve& rhs)const
  {
          /*if (abs(x - rhs->x) <= (w + rhs->w) / 2 && abs(y - rhs->y) <= (h +
  rhs->h) / 2) { if (Priority < rhs->Priority)return true; return false;
          }
          if (y+h/2 < rhs->y+rhs->h/2)return true;
          return false;
          return Priority < rhs.Priority;
  }*/
  friend bool compRR(const IRenderReserve* lhs, const IRenderReserve* rhs);
  friend CRenderReserveList;
};

bool compRR(const IRenderReserve* lhs, const IRenderReserve* rhs);