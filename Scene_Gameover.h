#pragma once
#include "Scene_Abstract.h"
#include "SceneManager.h"
#include "CSTGInputManager.h"
#include <memory>
#include "CTextDrawer.h"

class Scene_Gameover : public Scene_Abstract {
public:
	Scene_Gameover(SceneManager* ScnMng);
	~Scene_Gameover() {}

	void Update();
	void Render()const;

private:
	std::weak_ptr<CSTGInputManager> input;
	CTextDrawer::Text text[3];
	int cnt;
};