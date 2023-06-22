#pragma once
#include <memory>

#include "Input/CSTGInputManager.h"
#include "Calc/CStatus.h"
#include "Graphic/Draw/CTextDrawer.h"
#include "SceneManager.h"
#include "Scene_Abstract.h"

class Scene_Upgrade : public Scene_Abstract {
 public:
  Scene_Upgrade(SceneManager* ScnMng);
  ~Scene_Upgrade() {}

  void Update();
  void Render() const;

 private:
  std::weak_ptr<CSTGInputManager> input_;
  CTextDrawer::Text text_[7];
  int cnt_;
  bool has_enough_money_;
  CStatus now_;
  CStatus next_;
};