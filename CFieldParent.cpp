#include "CFieldParent.h"
#include "CField.h"
#include "CField_Grass.h"
#include "CField_IceFloor.h"
#include "CField_Wall.h"
#include "CAnchor.h"
#include <math.h>
#include <algorithm>

CFieldParent::CFieldParent(std::shared_ptr<CGameMediator> m, std::string filename)
	:fieldHolder(std::make_shared<CFieldHolder>(filename))
{
	CAnchor::getIns().setScrollLimit(CVector(fieldHolder->getWidth(), fieldHolder->getHeight()));
}

CFieldParent::~CFieldParent()
{
	OutputDebugString("CFieldParent‚ÍÁ‚¦‚Ä‚é");
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
	fieldHolder->getFloor(x, y)->setFrictionForce(m);

	for (int ay = max(0, y - 3); ay < min(fieldHolder->getHeight(), (int)y + 3); ay++) {
		for (int ax = max(0, x - 3); ax < min((int)fieldHolder->getWidth(), (int)x + 3); ax++) {
			fieldHolder->getWall(ax, ay)->Hit(m);
		}
	}
}

std::vector<CVector> CFieldParent::getRoute(CVector start, CVector goal, CAttribute attrDEF)
{
	return fieldHolder->Find_Route(start, goal, attrDEF);
}

void CFieldParent::Render() const
{
	fieldHolder->Render();
}
