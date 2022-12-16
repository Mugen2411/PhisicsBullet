#include "CField.h"
#include "CMover_ShotBase.h"
#include "CMover_BulletBase.h"

CField::CField(std::string gid, CVector position, CVector size, COF cofs, double temperature, CAttribute damage, bool isWall)
	:GID(gid), Position(position), Size(size), Cofs(cofs), Temperature(temperature), Damage(damage), DamageInterval(0), isWall(isWall)
{
}

void CField::setFrictionForce(CMover* m)
{
	m->ApplyFrictionForce(Cofs.FrictionCF);
	m->ApplyWaterRegistance(Cofs.WaterResCF);
	if (DamageInterval == 0 || m->getStatus() == CMover::STATUS::DEAD) {
		m->FieldDispatch(this);
		CAttribute t = m->TestDamage(Damage);
		if(Damage.Sum() < t.Sum())m->RatioDamage(Damage / 10.0, 1);
	}
	DamageInterval++;
	DamageInterval %= 6;
}

void CField::Update()
{
}

void CField::Render()const
{
}

void CField::attributeEffect(CMover_ShotBase* m) {
	attributeReaction(m->getBaseAttribute());
}

void CField::attributeEffect(CMover_BulletBase* m) {
	attributeReaction(m->getBaseAttribute());
}

void CField::Save(std::ofstream& fout) {
	fout << GID << "\n";
}
