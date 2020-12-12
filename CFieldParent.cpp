#include "CFieldParent.h"
#include "CField.h"
#include "CField_Grass.h"
#include "CField_IceFloor.h"
#include "CField_Wall.h"
#include <math.h>

CFieldParent::CFieldParent(CGameMediator* m)
{
	for (int y = 0; y < 15; y++) {
		std::vector<std::shared_ptr<CField>> f(20);
		for (int x = 0; x < 20; x++) {
			if ((!(rand() % 9) || (x == 0) || (x == 19) || (y == 0) || (y == 14))) {
				f[x] = std::make_shared<CField_Wall>(this, CVector(x * 32.0 + 16.0, y * 32.0 + 16.0), 0, 0);
				continue;
			}
			if ((x < 10 && y < 8) || (x > 9 && y > 7))f[x] = std::make_shared<CField_Grass>(this, CVector(x * 32.0 + 16.0, y * 32.0 + 16.0));
			else f[x] = std::make_shared<CField_IceFloor>(this, CVector(x * 32.0 + 16.0, y * 32.0 + 16.0));
		}
		fieldlist.push_back(f);
	}
}

void CFieldParent::Update()
{
	for (auto y = fieldlist.begin(); y != fieldlist.end(); y++) {
		for (auto x = y->begin(); x != y->end(); x++) {
			(*x)->Update();
		}
	}
}

void CFieldParent::ApplyForceToMover(CMover* m)
{
	CVector p = m->getPosition();
	int x = p.x / 32;
	int y = p.y / 32;
	fieldlist.at(y).at(x)->setFrictionForce(m);

	for (int ay = max(0, y - 3); ay < min((int)fieldlist.size(), (int)y + 3); ay++) {
		for (int ax = max(0, x - 3); ax < min((int)fieldlist[y].size(), (int)x + 3); ax++) {
			fieldlist.at(ay).at(ax)->Hit(m);
		}
	}
}

void CFieldParent::Render() const
{
	for (auto y = fieldlist.begin(); y != fieldlist.end(); y++) {
		for (auto x = y->begin(); x != y->end(); x++) {
			(*x)->Render();
		}
	}
}
