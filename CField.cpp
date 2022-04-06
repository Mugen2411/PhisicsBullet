#include "CField.h"

CField::CField(std::string gid, CVector position, CVector size, COF cofs, double temperature, CAttribute damage, bool isWall)
	:GID(gid), Position(position), Size(size), Cofs(cofs), Temperature(temperature), Damage(damage), DamageInterval(0), isWall(isWall)
{
}

void CField::setFrictionForce(CMover* m)
{
	m->ApplyFrictionForce(Cofs.FrictionCF);
	m->ApplyWaterRegistance(Cofs.WaterResCF);
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
