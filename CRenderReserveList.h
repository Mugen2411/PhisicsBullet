#pragma once
#include "IRenderReserve.h"
#include <list>
#include <vector>
#include <memory>
#include <algorithm>
#include "Constant.h"

class CRenderReserveList
{
	static std::list<IRenderReserve*> list;
public:
	inline static void Add(IRenderReserve* v) {
		if (v->x - v->w > Constant::ScreenW+32 ||
			v->x + v->w < -32 || v->y - v->h > Constant::ScreenH+32 || v->y + v->h < -32) {
			delete v;
			return;
		}
		list.push_back(v);
	}
	static void Render();
	friend IRenderReserve;
};