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
protected:
	int brightScreen;
	int shadowScreen;

	friend Singleton<CEffect_Bright>;
};