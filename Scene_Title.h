#pragma once
#include "Scene_Abstract.h"
#include "SceneManager.h"
#include "CSTGInputManager.h"
#include "CMenuSelecter.h"
#include <memory>
#include "CTextDrawer.h"

class Scene_Title : public Scene_Abstract {
public:
	Scene_Title(SceneManager* ScnMng);
	~Scene_Title() {}

	void Update();
	void Render()const;

private:
	std::weak_ptr<CSTGInputManager> input;
	CMenuSelecter CMS;
	CTextDrawer::Text menuText[4];
	CTextDrawer::Text titleText;
	int currentStage;
};