#include "Clooper.h"
#include "CRenderReserveList.h"
#include "CControllerFactory.h"
#include "CGameMediator.h"
#include "CMapEditor.h"
#include "Scene_Title.h"
#include "Scene_Gameover.h"
#include "Scene_Stageclear.h"
#include "Scene_Gameclear.h"
#include "Scene_Upgrade.h"
#include "Scene_Abstract.h"
#include "CTextDrawer.h"
#include "CAnchor.h"
#include "CProgressData.h"

CGame::CGame() :fps(), isQuit(false)
{
	ChangeScene(Constant::SCENE_ID::SCENE_TITLE, true);
}

CGame::~CGame()
{
	_scene.clear();
}

void CGame::Run()
{
	CControllerFactory::getIns().update();
	CAnchor::getIns().Update();
	(*_scene.begin())->Update();
	if (_scene.empty())return;
	fps.Update();
	for (auto& i : _scene) {
		i->Render();
	}
	CRenderReserveList::Render();
	CTextDrawer::getIns().Render();
	CTextDrawer::getIns().Clear();
	fps.Draw();
	fps.Wait();
}

void CGame::ChangeScene(int Scene, bool isStackClear)
{
	if (isStackClear) {
		_scene.clear();
	}
	switch (Scene) {
	case Constant::SCENE_ID::SCENE_MAIN:
		{auto s = std::make_shared<CGameMediator>(this);
		s->CreateParts();
		_scene.push_front(s); }
		break;
	case Constant::SCENE_ID::SCENE_EDITOR:
		_scene.push_front(std::make_shared <CMapEditor>(this));
		break;
	case Constant::SCENE_ID::SCENE_TITLE:
		_scene.push_front(std::make_shared <Scene_Title>(this));
		break;
	case Constant::SCENE_ID::SCENE_QUIT:
		isQuit = true;
		break;
	case Constant::SCENE_ID::SCENE_GAMEOVER:
		_scene.push_front(std::make_shared<Scene_Gameover>(this));
		break;
	case Constant::SCENE_ID::SCENE_STAGECLEAR:
		_scene.push_front(std::make_shared<Scene_Stageclear>(this));
		break;
	case Constant::SCENE_ID::SCENE_UPGRADE:
		_scene.push_front(std::make_shared<Scene_Upgrade>(this));
		break;
	case Constant::SCENE_ID::SCENE_GAMECLEAR:
		_scene.push_front(std::make_shared<Scene_Gameclear>(this));
		break;
	}
}
