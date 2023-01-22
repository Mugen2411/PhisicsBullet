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
  std::weak_ptr<CSTGInputManager> input_;
  CTextDrawer::Text text_[5];
  std::vector<int> skill_list_;
  int cnt_;
  int cur_;
};