#pragma once
#include <memory>

#include "Input/CSTGInputManager.h"
#include "Graphic/Draw/CTextDrawer.h"
#include "SceneManager.h"
#include "Scene_Abstract.h"

class Scene_Gameclear : public Scene_Abstract {
 public:
  Scene_Gameclear(SceneManager* ScnMng);
  ~Scene_Gameclear() {}

  void Update();
  void Render() const;

 private:
  std::weak_ptr<CSTGInputManager> input_;
  CTextDrawer::Text text_[4];
  int cnt_;
};