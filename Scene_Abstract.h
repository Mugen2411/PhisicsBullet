#pragma once
#include <DxLib.h>
#include "SceneManager.h"

class Scene_Abstract
{
protected:
	SceneManager *scn_mng;
public:
	Scene_Abstract(SceneManager *scn_mng);
	virtual ~Scene_Abstract();
	virtual void update() = 0;
	virtual void render() const = 0;
};
