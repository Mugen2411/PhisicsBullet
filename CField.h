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
		double frictionCF, double temperature, double reflectCF, CAttribute damage = CAttribute(0.0));
	virtual ~CField() {};

	bool operator ==(std::string gid)const;
	std::string getGID();

	virtual void setFrictionForce(CMover*);
	virtual CField* Clone(CVector position) = 0;

	virtual void Hit(CMover* m) {}		//ãﬂÇ≠Ç…ï®ëÃÇ™Ç†ÇÈÇ∆Ç´Ç…åƒÇŒÇÍÇÈÅAâΩÇ‡ÇµÇΩÇ≠Ç»ÇØÇÍÇŒÇµÇ»Ç≠ÇƒÇ‡Ç¢Ç¢
	virtual void Update();
	virtual void Render()const;

	void Save(std::ofstream &fout);
};

