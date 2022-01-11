#pragma once
#include "CFieldParent.h"
#include "CMover.h"
#include "CVector.h"
#include "CImage.h"
#include "CImageManager.h"
#include "CAttribute.h"
#include <memory>
#include <string>
#include <vector>
#include <fstream>

class CField
{
private:
	int DamageInterval;
protected:
	CVector Position;
	CVector Size;
	double FrictionCF;
	double Temperature;
	double ReflectCF;
	CAttribute Damage;

	std::string GID;

public:

	CField(std::string gid, CVector position, CVector size,
		double frictionCF, double temperature, double reflectCF, CAttribute damage = CAttribute(0, 0, 0, 0, 0, 0));
	virtual ~CField() {};
	virtual void setFrictionForce(CMover*);

	virtual void Hit(CMover* m) {}		//近くに物体があるときに呼ばれる、何もしたくなければしなくてもいい
	virtual void Update();
	virtual void Render()const;

	void Save(std::ofstream &fout);
};

