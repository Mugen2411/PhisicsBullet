#pragma once
#include <memory>

#include "Calc/CMenuSelecter.h"
#include "Input/CSTGInputManager.h"
#include "Graphic/Draw/CTextDrawer.h"
#include "Scene/SceneManager.h"
#include "Scene/Scene_Abstract.h"

class Scene_Option : public Scene_Abstract {
 public:
  Scene_Option(SceneManager* ScnMng);
  ~Scene_Option() {
    char n[256];
    GetModuleFileName(NULL, n, 256);
    ShellExecute(NULL, "open", n, NULL, NULL, SW_SHOW);
    scene_manager_->ChangeScene(Constant::SceneID::kSceneQuit, NULL);
  }

  void Update();
  void Render() const;

 private:
  std::weak_ptr<CSTGInputManager> input_;
  CTextDrawer::Text text_[4];
  std::string scaling_option_[2];
  std::string sound_option_[2];
  CMenuSelector menu_selector_;
  int cnt_;
};