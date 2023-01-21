#include "Clooper.h"

#include "CAnchor.h"
#include "CControllerFactory.h"
#include "CGameMediator.h"
#include "CMapEditor.h"
#include "CProgressData.h"
#include "CRenderReserveList.h"
#include "CTextDrawer.h"
#include "Scene_Abstract.h"
#include "Scene_Gameclear.h"
#include "Scene_Gameover.h"
#include "Scene_Option.h"
#include "Scene_Stageclear.h"
#include "Scene_Title.h"
#include "Scene_Upgrade.h"

CGame::CGame() : fps(), isQuit(false) {
  ChangeScene(Constant::SCENE_ID::SCENE_TITLE, true);
}

CGame::~CGame() { _scene.clear(); }

void CGame::Run() {
  CControllerFactory::getIns().update();
  CAnchor::getIns().Update();
  (*_scene.begin())->Update();
  if (_scene.empty()) return;
  fps.Update();
  int size = _scene.size();
  auto itr = _scene.begin();
  for (int i = 0; i < size; i++) {
    CTextDrawer::getIns().setPriority(i);
    (*itr)->Render();
    ++itr;
  }
  CRenderReserveList::Render();
  CTextDrawer::getIns().Render();
  CTextDrawer::getIns().Clear();
  fps.Draw();
  fps.Wait();
}

void CGame::PopScene() {
  if (_scene.size() < 2) return;
  _scene.pop_front();
}

void CGame::ChangeScene(int Scene, bool isStackClear) {
  if (isStackClear) {
    _scene.clear();
  }
  switch (Scene) {
    case Constant::SCENE_ID::SCENE_MAIN: {
      auto s = new CGameMediator(this);
      s->CreateParts();
      _scene.push_front(std::unique_ptr<CGameMediator>(s));
    } break;
    case Constant::SCENE_ID::SCENE_EDITOR:
      _scene.push_front(std::make_unique<CMapEditor>(this));
      break;
    case Constant::SCENE_ID::SCENE_TITLE:
      _scene.push_front(std::make_unique<Scene_Title>(this));
      break;
    case Constant::SCENE_ID::SCENE_QUIT:
      isQuit = true;
      break;
    case Constant::SCENE_ID::SCENE_GAMEOVER:
      _scene.push_front(std::make_unique<Scene_Gameover>(this));
      break;
    case Constant::SCENE_ID::SCENE_STAGECLEAR:
      _scene.push_front(std::make_unique<Scene_Stageclear>(this));
      break;
    case Constant::SCENE_ID::SCENE_UPGRADE:
      _scene.push_front(std::make_unique<Scene_Upgrade>(this));
      break;
    case Constant::SCENE_ID::SCENE_GAMECLEAR:
      _scene.push_front(std::make_unique<Scene_Gameclear>(this));
      break;
    case Constant::SCENE_ID::SCENE_OPTION:
      _scene.push_front(std::make_unique<Scene_Option>(this));
      break;
  }
}
