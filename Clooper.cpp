#include "Clooper.h"
#include "CRenderReserveList.h"
#include "CControllerFactory.h"
#include "CGameMediator.h"
#include "CMapEditor.h"
#include "Scene_Title.h"
#include "Scene_Abstract.h"
#include "CTextDrawer.h"
#include "CAnchor.h"
#include "CProgressData.h"

CGame::CGame():fps(),isQuit(false)
{
	ChangeScene(Constant::SCENE_ID::SCENE_TITLE, true);
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
	if (_scene.empty())return;
	fps.Update();
	_scene.top()->Render();
	CRenderReserveList::Render();
	CTextDrawer::getIns().Render();
	CTextDrawer::getIns().Clear();
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
	case Constant::SCENE_ID::SCENE_TITLE:
		_scene.push(std::make_shared <Scene_Title>(this));
		break;
	case Constant::SCENE_ID::SCENE_QUIT:
		isQuit = true;
		break;
	}
}
