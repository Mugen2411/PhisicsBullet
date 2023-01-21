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
  std::weak_ptr<CSTGInputManager> input;
  CMenuSelecter CMS;
  CTextDrawer::Text menuText[6];
  CTextDrawer::Text titleText;
  CTextDrawer::Text underText[6];
  int currentStage;
};