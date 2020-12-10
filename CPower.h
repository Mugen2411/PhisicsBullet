#pragma once
#include "CPowerParent.h"
#include "CMover.h"

class CPower
{
protected:
	CPowerParent* parent;
	CVector Position;
	double Power;
public:
	CPower(CPowerParent* p, CVector position, double power);

	virtual void ApplyForceToMover(CMover*) = 0;
	virtual int Update() = 0;
	virtual void Render()const = 0;
};

