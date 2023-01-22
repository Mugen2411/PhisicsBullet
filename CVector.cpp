#include "CVector.h"
#include "Constant.h"

CVector::CVector() : x(0.0), y(0.0) {}

CVector::CVector(double x, double y) : x(x), y(y) {}

CVector::CVector(double angle) : x(cos(angle)), y(sin(angle)) {}

CVector::CVector(int x, int y) : x(x), y(y) {}

CVector::CVector(bool v) : x(0), y(0) { is_valid = false; }

int CVector::GetDirection() {
  double angle = GetAngle();
  angle = std::fmod(angle + Constant::kPI * 2, Constant::kPI * 2);
  if (Constant::kPI / 4.0 * 5.0 < angle && angle <= Constant::kPI / 4.0 * 7.0)
    return 2;
  if (Constant::kPI / 4.0 * 3.0 < angle && angle <= Constant::kPI / 4.0 * 5.0)
    return 1;
  if (Constant::kPI / 4.0 < angle && angle <= Constant::kPI / 4.0 * 3.0)
    return 0;
  return 3;
}

CVector CVector::GetNorm() const {
  double l = GetLength();
  if (l < Constant::kZeroBorder) return CVector(0.0, 0.0);
  return *this / l;
}