#pragma once
#include "Singleton.h"
#include "CVector.h"
#include <list>

class CEffect_Bright : public Singleton<CEffect_Bright> {
public:
	struct BrightDesc{
		CVector position;
		double radius;
		int power;
	};

	void Register(BrightDesc b) {
		list.emplace_back(b);
	}
	void setBrightLevel(double l) {
		brightLevel = l;
	}
	void Render()const;
	void Clear() {
		list.clear();
	}

	void setOffScreen(int screen) {
		offscreen = screen;
	}

protected:
	CEffect_Bright();

	int offscreen;
	int brightScreen;
	int shadowScreen;
	int brightBuffer;
	int shadowBuffer;
	double brightLevel;
	int brightGraph;

	std::list<BrightDesc> list;

	friend Singleton<CEffect_Bright>;
};