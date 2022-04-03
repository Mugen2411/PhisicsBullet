#pragma once
#include "IRenderReserve.h"
#include <list>

class CRenderReserveList
{
	static std::list<IRenderReserve*> list;
public:
	inline static void Add(IRenderReserve* v) {
		list.push_back(v);
	}
	static void Render();
};

