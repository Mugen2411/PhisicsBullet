#pragma once
#include <memory>
#include <vector>

#include "CSTGInputManager.h"
#include "CTextDrawer.h"
#include "SceneManager.h"
#include "Scene_Abstract.h"

class Scene_Stageclear : public Scene_Abstract {
 public:
  Scene_Stageclear(SceneManager* ScnMng);
  ~Scene_Stageclear() {}

  void Update();
  void Render() const;

 private:
  std::weak_ptr<CSTGInputManager> input;
  CTextDrawer::Text text[5];
  std::vector<int> skillList;
  int cnt;
  int cur;
};