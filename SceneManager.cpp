#include "SceneManager.h"
#include "Scene_Abstract.h"


SceneManager::SceneManager()
{
}


SceneManager::~SceneManager()
{
}

void SceneManager::update()
{
	if (!_scene.empty())(* _scene.begin())->Update();
}

void SceneManager::render()
{
	if (!_scene.empty())(*_scene.begin())->Render();
}
