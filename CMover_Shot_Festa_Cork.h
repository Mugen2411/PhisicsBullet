#pragma once
#include "CMover_ShotBase.h"

class CMover_Shot_Festa_Cork : public CMover_ShotBase
{
public:
	CMover_Shot_Festa_Cork(CAttribute baseATK, CVector position, double angle);
	int Update();
	void Render()const;
};

