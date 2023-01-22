#pragma once
#include <memory>

#include "CSTGInputManager.h"
#include "CTextDrawer.h"
#include "SceneManager.h"
#include "Scene_Abstract.h"

class Scene_Gameover : public Scene_Abstract {
 public:
  Scene_Gameover(SceneManager* ScnMng);
  ~Scene_Gameover() {}

  void Update();
  void Render() const;

 private:
  std::weak_ptr<CSTGInputManager> input_;
  CTextDrawer::Text text_[3];
  int cnt_;
};