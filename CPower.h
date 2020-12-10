#pragma once
#include "CPowerParent.h"
#include "CMover.h"

class CPower
{
	CPowerParent* parent;
public:
	CPower(CPowerParent* p);

	virtual void ApplyForceToMover(CMover*) = 0;
	virtual int Update() = 0;
};

