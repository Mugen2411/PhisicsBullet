#pragma once
#include "IRenderReserve.h"
#include <list>
#include <vector>
#include <memory>
#include <algorithm>

class CRenderReserveList
{
	static std::list<IRenderReserve*> list;
public:
	inline static void Add(IRenderReserve* v) {
		list.push_back(v);
	}
	static void Render();
};