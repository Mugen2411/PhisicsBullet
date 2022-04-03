#pragma once
#include "CParts.h"
#include "CMover.h"
#include <vector>
#include <memory>

class CGameMediator;

class CMoverParent
{
	int cnt;
	std::weak_ptr<CGameMediator> med;
	std::vector<std::shared_ptr<CMover>> moverList;
	std::vector<std::shared_ptr<CMover>> reserveList;
public:
	CMoverParent(std::shared_ptr<CGameMediator>);
	inline void RegisterMover(std::shared_ptr<CMover> m) {
		reserveList.push_back(m);
	}
	std::weak_ptr<CMover> getMover(int ID, int num);
	void Update();
	void Render();

	void Hit();
};

