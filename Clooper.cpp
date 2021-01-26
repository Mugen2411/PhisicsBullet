#include "Clooper.h"

CGame::CGame():gameM(this),fps()
{
	ChangeScene(SCENE_MAIN, true);
}

void CGame::Run()
{
	_scene.top()->Update();
	_scene.top()->Render();
	fps.Update();
	fps.Draw();
	fps.Wait();
}

void CGame::ChangeScene(int Scene, bool isStackClear)
{
	if (isStackClear) {
		while (!_scene.empty()) {
			_scene.pop();
		}
	}
	switch (Scene) {
	case SCENE_MAIN:
		_scene.push(std::make_shared<CGameMediator>(this));
		break;
	}
}
