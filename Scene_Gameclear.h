#pragma once
#include <memory>

#include "CSTGInputManager.h"
#include "CTextDrawer.h"
#include "SceneManager.h"
#include "Scene_Abstract.h"

class Scene_Gameclear : public Scene_Abstract {
 public:
  Scene_Gameclear(SceneManager* ScnMng);
  ~Scene_Gameclear() {}

  void Update();
  void Render() const;

 private:
  std::weak_ptr<CSTGInputManager> input;
  CTextDrawer::Text text[4];
  int cnt;
};