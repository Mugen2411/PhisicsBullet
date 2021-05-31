#include "CFieldParent.h"
#include "CField.h"
#include "CField_Grass.h"
#include "CField_IceFloor.h"
#include "CField_Wall.h"
#include <math.h>
#include <algorithm>

CFieldParent::CFieldParent(std::shared_ptr<CGameMediator> m, int fieldWidth, int fieldHeight)
	:floorHolder(std::make_shared<CFieldHolder>(fieldWidth, fieldHeight)),
	wallHolder(std::make_shared<CFieldHolder>(fieldWidth, fieldHeight))
{

}

void CFieldParent::Update()
{
	floorHolder->Update();
}

void CFieldParent::ApplyForceToMover(CMover* m)
{
	CVector p = m->getPosition();
	int x = p.x / 32;
	int y = p.y / 32;
	floorHolder->getField(x, y)->setFrictionForce(m);

	for (int ay = max(0, y - 3); ay < min(floorHolder->getHeight(), (int)y + 3); ay++) {
		for (int ax = max(0, x - 3); ax < min((int)floorHolder->getWidth(), (int)x + 3); ax++) {
			floorHolder->getField(ax, ay)->Hit(m);
		}
	}
}

void CFieldParent::Render() const
{
	floorHolder->Render();
}
