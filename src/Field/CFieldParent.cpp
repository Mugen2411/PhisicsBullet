#include "CFieldParent.h"

#include <math.h>

#include <algorithm>

#include "Graphic/CAnchor.h"
#include "Field/CField.h"
#include "Field/Floor/CField_Grass.h"
#include "Field/Floor/CField_IceFloor.h"
#include "Field/Wall/CField_Wall.h"

CFieldParent::CFieldParent(CGameMediator* m, std::string filename)
    : field_holder_(new CFieldHolder(filename)), med_(m) {}

CFieldParent::~CFieldParent() {}

void CFieldParent::Update() { field_holder_->Update(); }

void CFieldParent::ApplyForceToMover(CMover* m) {
  CVector p = m->GetPosition();
  int x = (int)p.x_ / 32;
  int y = (int)p.y_ / 32;
  if (x < 0) m->SetStatus(1);
  if (y < 0) m->SetStatus(1);
  if (x >= field_holder_->GetWidth()) m->SetStatus(1);
  if (y >= field_holder_->GetHeight()) m->SetStatus(1);
  if (m->GetStatus() != 0) return;

  p = m->GetPosition();
  x = (int)(p.x_ / 32);
  y = (int)(p.y_ / 32);

  field_holder_->GetWall(x, y)->SetFrictionForce(m);
  field_holder_->GetFloor(x, y)->SetFrictionForce(m);
}

bool CFieldParent::HitToMover(CMover* m) {
  CVector p = m->GetPosition();
  int x = (int)p.x_ / 32;
  int y = (int)p.y_ / 32;
  int size =
      (int)((m->GetVelocity() + m->GetAcceleration()).GetLength2() / (16 * 16)) + 1;



  bool hitted = false;
  for (int ay = max(0, y - size);
       ay < min(field_holder_->GetHeight(), y + size + 1); ay++) {
    for (int ax = max(0, x - size);
         ax < min((int)field_holder_->GetWidth(), x + size + 1); ax++) {
      hitted |= field_holder_->GetWall(ax, ay)->Hit(m);
    }
  }
  return hitted;
}

std::list<CVector> CFieldParent::GetRoute(CVector start, CVector goal,
                                          CAttribute attrDEF, int distance) {
  return field_holder_->FindRoute(start, goal, attrDEF, distance);
}

std::vector<CVector> CFieldParent::GetTargetByDistance(CVector start,
                                                       int distance) {
  return field_holder_->FindTargetByDistance(start, distance);
}

void CFieldParent::Render() const { field_holder_->Render(); }