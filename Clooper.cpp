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

CGame::CGame() : fps_(), is_quit_(false) {
  ChangeScene(Constant::SceneID::kSceneTitle, true);
}

CGame::~CGame() { scene_.clear(); }

void CGame::Run() {
  CControllerFactory::GetIns().Update();
  CAnchor::GetIns().Update();
  (*scene_.begin())->Update();
  if (scene_.empty()) return;
  fps_.Update();
  int size = (int) scene_.size();
  auto itr = scene_.begin();
  for (int i = 0; i < size; i++) {
    CTextDrawer::GetIns().SetPriority(i);
    (*itr)->Render();
    ++itr;
  }
  CRenderReserveList::Render();
  CTextDrawer::GetIns().Render();
  CTextDrawer::GetIns().Clear();
  fps_.Draw();
  fps_.Wait();
}

void CGame::PopScene() {
  if (scene_.size() < 2) return;
  scene_.pop_front();
}

void CGame::ChangeScene(int Scene, bool isStackClear) {
  if (isStackClear) {
    scene_.clear();
  }
  switch (Scene) {
    case Constant::SceneID::kSceneMain: {
      auto s = new CGameMediator(this);
      s->CreateParts();
      scene_.push_front(std::unique_ptr<CGameMediator>(s));
    } break;
    case Constant::SceneID::kSceneEditor:
      scene_.push_front(std::make_unique<CMapEditor>(this));
      break;
    case Constant::SceneID::kSceneTitle:
      scene_.push_front(std::make_unique<Scene_Title>(this));
      break;
    case Constant::SceneID::kSceneQuit:
      is_quit_ = true;
      break;
    case Constant::SceneID::kSceneGameover:
      scene_.push_front(std::make_unique<Scene_Gameover>(this));
      break;
    case Constant::SceneID::kSceneStageclear:
      scene_.push_front(std::make_unique<Scene_Stageclear>(this));
      break;
    case Constant::SceneID::kSceneUpgrade:
      scene_.push_front(std::make_unique<Scene_Upgrade>(this));
      break;
    case Constant::SceneID::kSceneGameclear:
      scene_.push_front(std::make_unique<Scene_Gameclear>(this));
      break;
    case Constant::SceneID::kSceneOption:
      scene_.push_front(std::make_unique<Scene_Option>(this));
      break;
  }
}
