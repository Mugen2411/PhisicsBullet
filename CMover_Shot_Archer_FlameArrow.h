#pragma once
#include "CMover_ShotBase.h"
#include "CEffect_Bright.h"

class CMover_Shot_Archer_FlameArrow : public CMover_ShotBase
{
public:
	CMover_Shot_Archer_FlameArrow(double baseATK, CVector position, double angle);
	int Update();
	void Render()const;
};

