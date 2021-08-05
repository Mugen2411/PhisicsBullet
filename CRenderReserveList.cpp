#include "CRenderReserveList.h"

std::list<IRenderReserve*> CRenderReserveList::list;

void CRenderReserveList::Add(IRenderReserve* v)
{
	list.push_back(v);
}

void CRenderReserveList::Render()
{
	list.sort(compRenderReserve);
	for (IRenderReserve* v : list) {
		v->Render();
	}
	auto itr = list.begin();
	while (list.size() != 0) {
		delete (*itr);
		itr = list.erase(itr);
	}
}
