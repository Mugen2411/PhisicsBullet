#pragma once
#include "CMover_ShotBase.h"

class CMover_Shot_Festa_Superball : public CMover_ShotBase
{
	int color;
public:
	CMover_Shot_Festa_Superball(double baseATK, CVector position, double angle);
	int Update();
	void Render()const;

	void ifonWall() {};
};

