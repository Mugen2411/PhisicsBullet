#include "Scene_Gallery.h"

#include "Calc/CPassiveSkill.h"
#include "Calc/CProgressData.h"
#include "Calc/CStatus.h"
#include "Graphic/CAnchor.h"
#include "Graphic/Image/CImageManager.h"
#include "Input/CControllerFactory.h"
#include "Sound/CSoundManager.h"

Scene_Gallery::Scene_Gallery(SceneManager* ScnMng) : Scene_Abstract(ScnMng), menu_selector_(3,0) {
  input_ = CControllerFactory::GetIns().GetController();
  input_.lock()->SetMouseInvisible();
}

void Scene_Gallery::Update() {
  if (input_.lock()->Down() == 1) {
    CSoundManager::GetIns().Find("cursor")->Play(CSound::PlayType::kBack);
    menu_selector_.Next();
  }
  if (input_.lock()->Up() == 1) {
    CSoundManager::GetIns().Find("cursor")->Play(CSound::PlayType::kBack);
    menu_selector_.Prev();
  }

  if (input_.lock()->Start() == 1) {
    CProgressData::GetIns().Save();
    scene_manager_->PopScene();
    return;
  }
}

void Scene_Gallery::Render() const {
  CAnchor::GetIns().EnableAbsolute();
  CImageManager::GetIns().Find("system_curtain")->Draw(0, 0, 0, 0);
  CImageManager::GetIns().Find("system_curtain")->Draw(320, 0, 0, 1);

  CImageManager::GetIns().Find("icon_return")->Draw(0, 0, 101);

  CAnchor::GetIns().DisableAbsolute();
}