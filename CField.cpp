#include "CField.h"

CField::CField(CFieldParent* f, CVector position, CVector size, double frictionCF, double temperature, double reflectCF)
	:parent(f), Position(position), Size(size), FrictionCF(frictionCF), Temperature(temperature), ReflectCF(reflectCF)
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
