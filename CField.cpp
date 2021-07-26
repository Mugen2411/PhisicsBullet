#include "CField.h"

CField::CField(std::string gid, CVector position, CVector size, double frictionCF, double temperature, double reflectCF)
	:GID(gid), Position(position), Size(size), FrictionCF(frictionCF), Temperature(temperature), ReflectCF(reflectCF)
{
}

void CField::setFrictionForce(CMover* m)
{
	m->ApplyFrictionForce(FrictionCF);
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
