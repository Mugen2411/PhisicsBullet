#pragma once
#include <memory>

#include "Constant.h"
#include "Fps.h"
#include "SceneManager.h"

class CGame : public SceneManager {
  Fps fps;
  bool isQuit;

 public:
  CGame();
  virtual ~CGame();

  void Run();
  void PopScene();
  void ChangeScene(int Scene, bool isStackClear);
  bool isQuitted() { return isQuit; }
};
