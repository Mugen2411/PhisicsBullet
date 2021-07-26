#pragma once
#include "CGameMediator.h"
#include "Scene_Abstract.h"
#include "SceneManager.h"
#include "Fps.h"
#include <memory>

class CGame: public SceneManager
{
	Fps fps;
public:
	CGame();
	virtual ~CGame();

	enum SCENE_ID {
		SCENE_MAIN, SCENE_EDITOR, SCENE_TITLE
	};
	void Run();
	void ChangeScene(int Scene, bool isStackClear);
};

