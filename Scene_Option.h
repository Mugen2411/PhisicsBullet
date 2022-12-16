#pragma once
#include "Scene_Abstract.h"
#include "SceneManager.h"
#include "CSTGInputManager.h"
#include <memory>
#include "CTextDrawer.h"

class Scene_Option : public Scene_Abstract {
public:
	Scene_Option(SceneManager* ScnMng);
	~Scene_Option() {
		char n[256];
		GetModuleFileName(NULL, n, 256);
		ShellExecute(NULL, "open", n, NULL, NULL, SW_SHOW);
		scn_mng->ChangeScene(Constant::SCENE_ID::SCENE_QUIT, NULL);
	}

	void Update();
	void Render()const;

private:
	std::weak_ptr<CSTGInputManager> input;
	CTextDrawer::Text text[3];
	std::string scalingOption[2];
	int cnt;
};