#pragma once
#include <vector>
#include <memory>
#include "Scene_Abstract.h"
#include "CControllerFactory.h"

class CMoverParent;
class CFieldParent;
class CPowerParent;

class CMover;

class CGameMediator: public Scene_Abstract, public std::enable_shared_from_this<CGameMediator>
{
protected:
	std::shared_ptr<CSTGInputManager> input;
	std::shared_ptr<CMoverParent> moverParent;
	std::shared_ptr<CFieldParent> fieldParent;
	std::shared_ptr<CPowerParent> powerParent;

	bool isPause;
	int pauseGuage;

public:
	CGameMediator(SceneManager *ScnMng);
	
	virtual void CreateParts();

	void RegisterMover(std::shared_ptr<CMover>);
	void ApplyForceToMover(CMover*);
	void Update();
	void Render()const;
};

