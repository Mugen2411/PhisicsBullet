#pragma once
#include "CFieldParent.h"
#include "CMover.h"
#include "CVector.h"
#include "CImage.h"
#include "CImageManager.h"
#include <memory>
#include <string>

class CField
{
protected:
	CVector Position;
	CVector Size;
	double FrictionCF;
	double Temperature;
	double ReflectCF;

	std::string GID;

public:

	CField(const char* gid, CVector position, CVector size, double frictionCF, double temperature, double reflectCF);
	virtual ~CField() {};
	virtual void setFrictionForce(CMover*);

	virtual void Hit(CMover* m) {}		//近くに物体があるときに呼ばれる、何もしたくなければしなくてもいい
	virtual void Update();
	virtual void Render()const;
};

