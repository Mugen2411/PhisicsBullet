#include "CField.h"

CField::CField(std::string gid, CVector position, CVector size, double frictionCF, double temperature, double reflectCF, CAttribute damage)
	:GID(gid), Position(position), Size(size), FrictionCF(frictionCF), Temperature(temperature), ReflectCF(reflectCF), Damage(damage),DamageInterval(0)
{
}


bool CField::operator==(std::string gid)const
{
	return (gid == GID);
}

std::string CField::getGID()
{
	return GID;
}

void CField::setFrictionForce(CMover* m)
{
	m->ApplyFrictionForce(FrictionCF);
	if(DamageInterval == 0)m->RatioDamage(Damage / 10.0, 1);
	DamageInterval++;
	DamageInterval %= 6;
}

void CField::Update()
{
}

void CField::Render()const
{
}

void CField::Save(std::ofstream& fout) {
	fout << GID << "\n";
}
