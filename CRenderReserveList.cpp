#include "CRenderReserveList.h"

#include "CEffect_Bright.h"

std::list<IRenderReserve*> CRenderReserveList::list_;

void CRenderReserveList::Render() {
  // std::sort(list_.begin(), list_.end(), compRR);
  list_.sort(compRR);
  for (auto& v : list_) {
    v->Render();
    delete v;
  }
  list_.clear();
  CEffect_Bright::GetIns().Render();
}