#pragma once
#include "CGameMediator.h"
#include "CMapEditor.h"
#include "Scene_Abstract.h"
#include "SceneManager.h"
#include "Fps.h"
#include <memory>
#include "Constant.h"

class CGame: public SceneManager
{
	Fps fps;
public:
	CGame();
	virtual ~CGame();

	void Run();
	void ChangeScene(int Scene, bool isStackClear);
};

