#include "CFieldParent.h"
#include "CField.h"
#include "CField_Grass.h"
#include "CField_IceFloor.h"
#include "CField_Wall.h"
#include <math.h>
#include <algorithm>

CFieldParent::CFieldParent(std::shared_ptr<CGameMediator> m) :fieldHolder(std::make_shared<CFieldHolder>(20,15))
{
	for (int y = 0; y < 15; y++) {
		for (int x = 0; x < 20; x++) {
			if ((!(rand() % 9) || (x == 0) || (x == 19) || (y == 0) || (y == 14))) {
				fieldHolder->write(std::make_shared<CField_Wall>(this, CVector(x * 32.0 + 16.0, y * 32.0 + 16.0), 0, 0), x, y);
				continue;
			}
			if ((x < 10 && y < 8) || (x > 9 && y > 7))fieldHolder->write(std::make_shared<CField_Grass>(this, CVector(x * 32.0 + 16.0, y * 32.0 + 16.0)), x, y);
			else fieldHolder->write(std::make_shared<CField_IceFloor>(this, CVector(x * 32.0 + 16.0, y * 32.0 + 16.0)), x, y);
		}
	}
}

void CFieldParent::Update()
{
	fieldHolder->Update();
}

void CFieldParent::ApplyForceToMover(CMover* m)
{
	CVector p = m->getPosition();
	int x = p.x / 32;
	int y = p.y / 32;
	fieldHolder->getField(x, y)->setFrictionForce(m);

	for (int ay = max(0, y - 3); ay < min(fieldHolder->getHeight(), (int)y + 3); ay++) {
		for (int ax = max(0, x - 3); ax < min((int)fieldHolder->getWidth(), (int)x + 3); ax++) {
			fieldHolder->getField(ax, ay)->Hit(m);
		}
	}
}

void CFieldParent::Render() const
{
	fieldHolder->Render();
}
