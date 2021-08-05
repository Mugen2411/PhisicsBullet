#pragma once
#include "IRenderReserve.h"
#include <list>

class CRenderReserveList
{
	static std::list<IRenderReserve*> list;
public:
	static void Add(IRenderReserve*);
	static void Render();
};

