#pragma once
#include "SceneManager.h"
#include "Fps.h"
#include <memory>
#include "Constant.h"

class CGame: public SceneManager
{
	Fps fps;
	bool isQuit;
public:
	CGame();
	virtual ~CGame();

	void Run();
	void PopScene();
	void ChangeScene(int Scene, bool isStackClear);
	bool isQuitted() {
		return isQuit;
	}
};

