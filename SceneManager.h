#pragma once
#include <stack>
#include <memory>

class Scene_Abstract;

class SceneManager
{
protected:
	std::stack<std::shared_ptr<Scene_Abstract>> _scene;
public:
	SceneManager();
	virtual ~SceneManager();

	virtual void ChangeScene(int Scene, bool isStackClear) = 0;
	void update();
	void render();
};

