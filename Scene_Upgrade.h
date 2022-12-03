#pragma once
#include "Scene_Abstract.h"
#include "SceneManager.h"
#include "CSTGInputManager.h"
#include <memory>
#include "CTextDrawer.h"
#include "CStatus.h"

class Scene_Upgrade : public Scene_Abstract {
public:
	Scene_Upgrade(SceneManager* ScnMng);
	~Scene_Upgrade() {}

	void Update();
	void Render()const;

private:
	std::weak_ptr<CSTGInputManager> input;
	CTextDrawer::Text text[7];
	int cnt;
	bool hasEnoughMoney;
	CStatus now;
	CStatus next;
};