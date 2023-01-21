#include "CFieldParent.h"

#include <math.h>

#include <algorithm>

#include "CAnchor.h"
#include "CField.h"
#include "CField_Grass.h"
#include "CField_IceFloor.h"
#include "CField_Wall.h"

CFieldParent::CFieldParent(CGameMediator* m, std::string filename)
    : fieldHolder(new CFieldHolder(filename)), med(m) {}

CFieldParent::~CFieldParent() {}

void CFieldParent::Update() { fieldHolder->Update(); }

void CFieldParent::ApplyForceToMover(CMover* m) {
  CVector p = m->getPosition();
  int x = p.x / 32;
  int y = p.y / 32;
  if (x < 0) m->setStatus(2);
  if (y < 0) m->setStatus(2);
  if (x > fieldHolder->getWidth()) m->setStatus(2);
  if (y > fieldHolder->getHeight()) m->setStatus(2);

  p = m->getPosition();
  x = p.x / 32;
  y = p.y / 32;

  /*if (fieldHolder->getWall(x, y)->isWall) {
          if (y < fieldHolder->getHeight() / 2)m->setPosition(p.y += 32);
          else m->setPosition(p.y -= 32);
          if (x < fieldHolder->getWidth() / 2)m->setPosition(p.x += 32);
          else m->setPosition(p.x -= 32);
  }*/
  fieldHolder->getWall(x, y)->setFrictionForce(m);
  fieldHolder->getFloor(x, y)->setFrictionForce(m);
  m->ApplyAirRegistance();
}

bool CFieldParent::HitToMover(CMover* m) {
  CVector p = m->getPosition();
  int x = p.x / 32;
  int y = p.y / 32;
  int size =
      ((m->getVelocity() + m->getAcceleration()).getLength2() / (16 * 16)) + 1;

  bool hitted = false;
  for (int ay = max(0, y - size);
       ay < min(fieldHolder->getHeight(), y + size + 1); ay++) {
    for (int ax = max(0, x - size);
         ax < min((int)fieldHolder->getWidth(), x + size + 1); ax++) {
      hitted |= fieldHolder->getWall(ax, ay)->Hit(m);
    }
  }
  return hitted;
}

std::list<CVector> CFieldParent::getRoute(CVector start, CVector goal,
                                          CAttribute attrDEF, int distance) {
  return fieldHolder->Find_Route(start, goal, attrDEF, distance);
}

std::vector<CVector> CFieldParent::getTargetByDistance(CVector start,
                                                       int distance) {
  return fieldHolder->findTargetByDistance(start, distance);
}

void CFieldParent::Render() const { fieldHolder->Render(); }
