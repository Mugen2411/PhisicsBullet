#pragma once
#include "CFieldParent.h"
#include "CMover.h"
#include "CVector.h"
#include <memory>

class CField
{
protected:
	CVector Position;
	CVector Size;
	CFieldParent* parent;
	double FrictionCF;
	double Temperature;
	double ReflectCF;
public:
	CField(CFieldParent* f, CVector position, CVector size, double frictionCF, double temperature, double reflectCF);
	virtual ~CField() {};
	virtual void setFrictionForce(CMover*);

	virtual void Hit(CMover* m) {}		//ãﬂÇ≠Ç…ï®ëÃÇ™Ç†ÇÈÇ∆Ç´Ç…åƒÇŒÇÍÇÈÅAâΩÇ‡ÇµÇΩÇ≠Ç»ÇØÇÍÇŒÇµÇ»Ç≠ÇƒÇ‡Ç¢Ç¢
	virtual void Update();
	virtual void Render()const;
};

