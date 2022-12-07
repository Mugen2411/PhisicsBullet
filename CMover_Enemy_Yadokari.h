#pragma once
#include "CMover_Enemy.h"

class CMover_Enemy_Yadokari :
	public CMover_EnemyBase
{
	CVector testDest;
	int cnt = 0;
public:
	CMover_Enemy_Yadokari(CVector position, int Level);
	int Update();
	void Render()const;

	CMover_EnemyBase* Clone(CVector Position, int Level);
};

