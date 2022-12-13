#include "CRenderReserveList.h"
#include "CEffect_Bright.h"

std::list<IRenderReserve*> CRenderReserveList::list;

void CRenderReserveList::Render()
{
	//std::sort(list.begin(), list.end(), compRR);
	list.sort(compRR);
	for (auto& v : list) {
		v->Render();
		delete v;
	}
	list.clear();
	CEffect_Bright::getIns().Render();
}