#pragma once
#include <list>
#include <memory>

class Scene_Abstract;

class SceneManager {
 public:
  SceneManager();
  virtual ~SceneManager();

  virtual void PopScene() = 0;
  virtual void ChangeScene(int Scene, bool isStackClear) = 0;
  void Update();
  void Render();

 protected:
  std::list<std::unique_ptr<Scene_Abstract>> scene_;
};
