#pragma once
#include <memory>

#include "CSTGInputManager.h"
#include "CStatus.h"
#include "CTextDrawer.h"
#include "SceneManager.h"
#include "Scene_Abstract.h"

class Scene_Upgrade : public Scene_Abstract {
 public:
  Scene_Upgrade(SceneManager* ScnMng);
  ~Scene_Upgrade() {}

  void Update();
  void Render() const;

 private:
  std::weak_ptr<CSTGInputManager> input;
  CTextDrawer::Text text[7];
  int cnt;
  bool hasEnoughMoney;
  CStatus now;
  CStatus next;
};