#include "CMenuSelecter.h"

void CMenuSelecter::prev() {
  m_cur += (m_max - 1);
  m_cur %= m_max;
}

void CMenuSelecter::next() {
  m_cur++;
  m_cur %= m_max;
}

int CMenuSelecter::get() const { return m_cur; }
