#include "SceneManager.h"

#include "Scene_Abstract.h"

SceneManager::SceneManager() {}

SceneManager::~SceneManager() {}

void SceneManager::Update() {
  if (!scene_.empty()) (*scene_.begin())->Update();
}

void SceneManager::Render() {
  if (!scene_.empty()) (*scene_.begin())->Render();
}
