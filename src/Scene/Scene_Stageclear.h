#pragma once
#include <memory>
#include <vector>

#include "Input/CSTGInputManager.h"
#include "Graphic/Draw/CTextDrawer.h"
#include "Scene/SceneManager.h"
#include "Scene/Scene_Abstract.h"

class Scene_Stageclear : public Scene_Abstract {
 public:
  Scene_Stageclear(SceneManager* ScnMng);
  ~Scene_Stageclear() {}

  void Update();
  void Render() const;

 private:
  std::weak_ptr<CSTGInputManager> input_;
  CTextDrawer::Text text_[6];
  std::vector<int> skill_list_;
  int cnt_;
  int cnt_color_;
  int cur_;
};