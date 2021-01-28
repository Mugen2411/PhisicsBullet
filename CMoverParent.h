#pragma once
#include "CParts.h"
#include "CMover.h"
#include <vector>
#include <memory>

class CGameMediator;

class CMoverParent
{
	int cnt;
	std::shared_ptr<CGameMediator> med;
	std::vector<std::shared_ptr<CMover>> moverList;
	std::vector<std::shared_ptr<CMover>> reserveList;
public:
	CMoverParent(std::shared_ptr<CGameMediator>);
	void RegisterMover(std::shared_ptr<CMover>);
	void Update();
	void Render();
};

