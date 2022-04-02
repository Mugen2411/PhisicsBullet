#include "Clooper.h"
#include "CRenderReserveList.h"
#include "CControllerFactory.h"
#include "CAnchor.h"

CGame::CGame():fps()
{
	ChangeScene(Constant::SCENE_ID::SCENE_MAIN, true);
}

CGame::~CGame()
{
	while (!_scene.empty()) {
		_scene.pop();
	}
}

void CGame::Run()
{
	CControllerFactory::getIns().update();
	CAnchor::getIns().Update();
	_scene.top()->Update();
	fps.Update();
	_scene.top()->Render();
	CRenderReserveList::Render();
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
	case Constant::SCENE_ID::SCENE_MAIN:
		{auto s = std::make_shared<CGameMediator>(this);
		s->CreateParts();
		_scene.push(s); }
		break;
	case Constant::SCENE_ID::SCENE_EDITOR:
		_scene.push(std::make_shared <CMapEditor>(this));
		break;
	}
}
