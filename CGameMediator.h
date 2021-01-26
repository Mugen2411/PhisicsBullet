#pragma once
#include <vector>
#include <memory>
#include "Scene_Abstract.h"
#include "CControllerFactory.h"

class CMoverParent;
class CFieldParent;
class CPowerParent;

class CMover;

class CGameMediator: public Scene_Abstract
{
protected:
	std::shared_ptr<CSTGInputManager> input;
	std::shared_ptr<CMoverParent> moverParent;
	std::shared_ptr<CFieldParent> fieldParent;
	std::shared_ptr<CPowerParent> powerParent;

	virtual void CreateParts();

	bool isPause;
	int pauseGuage;

public:
	CGameMediator(SceneManager *ScnMng);
	
	void ApplyForceToMover(CMover*);
	void Update();
	void Render()const;
};

