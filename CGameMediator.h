#pragma once
#include <vector>
#include <memory>

class CMoverParent;
class CFieldParent;
class CPowerParent;

class CMover;

class CGameMediator
{
protected:
	std::shared_ptr<CMoverParent> moverParent;
	std::shared_ptr<CFieldParent> fieldParent;
	std::shared_ptr<CPowerParent> powerParent;

	virtual void CreateParts();

public:
	CGameMediator();

	void ApplyForceToMover(CMover*);
	void Update();
	void Render()const;
};

