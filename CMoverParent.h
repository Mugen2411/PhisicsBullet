#pragma once
#include "CParts.h"
#include "CMover.h"
#include <vector>
#include <memory>

class CGameMediator;

class CMoverParent
{
	int cnt;
	CGameMediator* med;
	std::vector<std::shared_ptr<CMover>> moverList;
public:
	CMoverParent(CGameMediator*);
	void Update();
	void Render();
};

