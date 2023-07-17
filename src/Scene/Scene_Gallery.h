#pragma once
#include <memory>

#include "Calc/CMenuSelecter.h"
#include "Input/CSTGInputManager.h"
#include "Graphic/Draw/CTextDrawer.h"
#include "Scene/SceneManager.h"
#include "Scene/Scene_Abstract.h"

class Scene_Gallery : public Scene_Abstract {
 public:
  Scene_Gallery(SceneManager* ScnMng);
  ~Scene_Gallery() {}

  void Update();
  void Render() const;

 private:
  std::weak_ptr<CSTGInputManager> input_;
  CMenuSelector menu_selector_;
};