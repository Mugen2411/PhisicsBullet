#pragma once
#include "CGameMediator.h"
#include "Scene_Abstract.h"
#include "SceneManager.h"
#include "Fps.h"

class CGame: public SceneManager
{
	Fps fps;
	CGameMediator gameM;
public:
	CGame();

	enum SCENE_ID {
		SCENE_MAIN, SCENE_EDITOR, SCENE_TITLE
	};
	void Run();
	void ChangeScene(int Scene, bool isStackClear);
};

