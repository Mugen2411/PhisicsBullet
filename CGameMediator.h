#pragma once
#include <vector>
#include <memory>
#include "Scene_Abstract.h"
#include "CControllerFactory.h"
#include "CVector.h"
#include "CAttribute.h"

class CMoverParent;
class CFieldParent;
class CPowerParent;

class CMover;

class CGameMediator: public Scene_Abstract, public std::enable_shared_from_this<CGameMediator>
{
protected:
	std::weak_ptr<CSTGInputManager> input;
	std::shared_ptr<CMoverParent> moverParent;
	std::shared_ptr<CFieldParent> fieldParent;
	std::shared_ptr<CPowerParent> powerParent;

	bool isPause;
	int pauseGuage;

	int reserveMoney=0;	//‘Þ‹p‚Å“¾‚ç‚ê‚é—\’è‚Ì‹à

public:
	CGameMediator(SceneManager *ScnMng);
	virtual ~CGameMediator();
	
	virtual void CreateParts();

	void RegisterMover(std::shared_ptr<CMover> m);
	void ApplyForceToMover(CMover*);
	CVector GetPlayerPosition();
	std::vector<CVector> GetRoute(CVector start, CVector goal, CAttribute attrDEF);
	std::weak_ptr<CMover> GetNearestMover(int ID, CVector p);
	void getMoney(int value);

	void Update();
	void Render()const;
};

