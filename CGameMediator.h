#pragma once
#include <vector>
#include <memory>
#include "SceneManager.h"
#include "CControllerFactory.h"

class CMoverParent;
class CFieldParent;
class CPowerParent;

class CMover;

class CGameMediator : public SceneManager
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
	CGameMediator();

	void ChangeScene(int Scene, bool isStackClear);
	
	void ApplyForceToMover(CMover*);
	void Update();
	void Render()const;
};

