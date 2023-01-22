#include "CPower.h"

CPower::CPower(CVector position, double power, int duration)
    : parent_(nullptr),
      position_(position),
      power_(power),
      duration_(duration),
      cnt_(0) {}
