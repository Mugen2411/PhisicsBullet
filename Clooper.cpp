#include "Clooper.h"

CGame::CGame():fps()
{
	ChangeScene(SCENE_MAIN, true);
}

CGame::~CGame()
{
	while (!_scene.empty()) {
		_scene.pop();
	}
}

void CGame::Run()
{
	_scene.top()->Update();
	fps.Update();
	_scene.top()->Render();
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
		auto s = std::make_shared<CGameMediator>(this);
		s->CreateParts();
		_scene.push(s);
		break;
	}
}
