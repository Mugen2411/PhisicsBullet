#pragma once
#include "Scene_Abstract.h"
#include "SceneManager.h"
#include "CSTGInputManager.h"
#include <memory>
#include "CTextDrawer.h"

class Scene_Stageclear : public Scene_Abstract {
public:
	Scene_Stageclear(SceneManager* ScnMng);
	~Scene_Stageclear() {}

	void Update();
	void Render()const;

private:
	std::weak_ptr<CSTGInputManager> input;
	CTextDrawer::Text text[4];
	int cnt;
};