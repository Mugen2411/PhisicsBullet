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
	virtual void Update() = 0;
	virtual void Render() const = 0;
};
