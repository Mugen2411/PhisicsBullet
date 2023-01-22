#include "CField_Wall.h"

#include <DxLib.h>

CField_Wall::CField_Wall(std::string gid_, CVector position_, COF cofs)
    : CField(gid_, position_, CVector(32.0, 32.0), cofs, 0.0, CAttribute(100.0),
             true) {}

bool CField_Wall::Hit(CMover* m) {
  if (is_wall_) {
    m->FieldDispatch(this);
    return m->OnWall(this, cofs_.ReflectCF);
  }
  return false;
}
