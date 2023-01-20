#pragma once
#include "CPowerParent.h"
#include "CMover.h"

class CPower
{
protected:
	CPowerParent* parent;
	CVector Position;
	double Power;
	int duration;
	int cnt;
public:
	CPower(CVector position, double power, int duration);
	void setParent(CPowerParent* p) {
		parent = p;
	}

	virtual void ApplyForceToMover(CMover*) = 0;
	virtual int Update() = 0;
	virtual void Render()const = 0;
};

