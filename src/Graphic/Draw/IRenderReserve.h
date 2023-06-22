#pragma once
#include <memory>

class CRenderReserveList;

class IRenderReserve {
 public:
  IRenderReserve(int GHandle, int Priority, double x, double y, double w,
                 double h);
  virtual ~IRenderReserve() {}

  IRenderReserve(const IRenderReserve& v);
  virtual void Render() const = 0;

 protected:
  const int graphic_handle_;
  const int priority_;
  const double x_, y_, w_, h_;

  friend bool compRR(const IRenderReserve* lhs, const IRenderReserve* rhs);
  friend CRenderReserveList;
};

bool compRR(const IRenderReserve* lhs, const IRenderReserve* rhs);