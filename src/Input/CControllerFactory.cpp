#include "CControllerFactory.h"

CControllerFactory::CControllerFactory() {
  current_ = std::make_shared<CKeyInputManager>();
}

std::weak_ptr<CSTGInputManager> CControllerFactory::GetController() {
  return current_;
}

void CControllerFactory::Update() { current_->Update(); }
