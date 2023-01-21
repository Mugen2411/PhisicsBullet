#pragma once
#include <memory>

#include "CKeyInputManager.h"
#include "Singleton.h"

class CControllerFactory : public Singleton<CControllerFactory> {
 protected:
  std::shared_ptr<CSTGInputManager> current;

 public:
  CControllerFactory();
  std::weak_ptr<CSTGInputManager> getController();
  void update();
};
