#include "CMenuSelecter.h"

void CMenuSelector::Prev() {
  cur_ += (max_ - 1);
  cur_ %= max_;
}

void CMenuSelector::Next() {
  cur_++;
  cur_ %= max_;
}

int CMenuSelector::Get() const { return cur_; }
