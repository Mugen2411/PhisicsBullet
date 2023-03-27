#pragma once
#include <memory>

#include "CMenuSelecter.h"
#include "CSTGInputManager.h"
#include "CTextDrawer.h"
#include "SceneManager.h"
#include "Scene_Abstract.h"

class Scene_Title : public Scene_Abstract {
 public:
  Scene_Title(SceneManager* ScnMng);
  ~Scene_Title() {}

  void Update();
  void Render() const;

 private:
  std::weak_ptr<CSTGInputManager> input_;
  CMenuSelector menu_selector_;
  CTextDrawer::Text menu_text_[6];
  CTextDrawer::Text title_text_;
  CTextDrawer::Text under_text_[6];
  int current_stage_;
  int current_level_endless_;
  const int kTextLeftLine = 360;
  const int kTextHighlightDiff = 20;
};