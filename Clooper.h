#pragma once
#include <memory>

#include "Constant.h"
#include "Fps.h"
#include "SceneManager.h"

class CGame : public SceneManager {
 public:
  CGame();
  virtual ~CGame();

  void Run();
  void PopScene();
  void ChangeScene(int Scene, bool isStackClear);
  bool IsQuitted() { return is_quit_; }

 private:
  Fps fps_;
  bool is_quit_;
};
