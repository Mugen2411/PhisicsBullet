#include "CMover.h"

#include "CField.h"

CMover::CMover(MoverID ID, CVector position, double size, CVector velocity,
               double mass, COF cofs, double temperature)
    : position_(position),
      velocity_(velocity),
      acceleration_(0.0, 0.0),
      size_(size * 0.5),
      mass_(mass),
      now_fricted_(0.0),
      now_water_forced_(0.0),
      cofs_(cofs),
      temperature_(temperature),
      status_(Status::kAlive),
      category_(ID) {}

void CMover::Hit(CMover* m) {}

void CMover::Hit(CMover_ShotBase* m) {}

void CMover::Hit(CMover_EnemyBase* m) {}

void CMover::Hit(CMover_Player*) {}

void CMover::Hit(CMover_BulletBase* m) {}

bool CMover::OnWall(CField* f, double WallReflectionCF) {
  CVector WallPosition = f->GetPosition();
  CVector WallSize = f->GetSize();
  CVector nextPosition = position_ + velocity_ + acceleration_;
  double max = (position_.x + size_) - (WallPosition.x - WallSize.x / 2),
         may = (position_.y + size_) - (WallPosition.y - WallSize.y / 2);
  double nax = (WallPosition.x + WallSize.x / 2) - (position_.x - size_),
         nay = (WallPosition.y + WallSize.y / 2) - (position_.y - size_);
  double _max = (nextPosition.x + size_) - (WallPosition.x - WallSize.x / 2),
         _may = (nextPosition.y + size_) - (WallPosition.y - WallSize.y / 2);
  double _nax = (WallPosition.x + WallSize.x / 2) - (nextPosition.x - size_),
         _nay = (WallPosition.y + WallSize.y / 2) - (nextPosition.y - size_);
  bool U = false, D = false, R = false, L = false;

  //カド同士の判定
  if (0 >= max && 0 >= may && _max > 0 && _may > 0) {
    if (_max >= _may) {
      //下にある
      D = true;
    } else {
      //右にある
      R = true;
    }
  }
  if (0 >= nax && 0 >= may && _nax > 0 && _may > 0) {
    if (_nax >= _may) {
      //下にある
      D = true;
    } else {
      //左にある
      L = true;
    }
  }
  if (0 >= max && 0 >= nay && _max > 0 && _nay > 0) {
    if (_max >= _nay) {
      //上にある
      U = true;
    } else {
      //右にある
      R = true;
    }
  }
  if (0 >= nax && 0 >= nay && _nax > 0 && _nay > 0) {
    if (_nax >= _nay) {
      //上にある
      U = true;
    } else {
      //左にある
      L = true;
    }
  }

  //上下左右の判定
  if (may > 0 && nay > 0) {
    if (_nax > 0 && (position_.x - size_) > (WallPosition.x - WallSize.x / 2)) {
      //左にある
      L = true;
    }
    if (_max > 0 && (WallPosition.x + WallSize.x / 2) > (position_.x + size_)) {
      //右にある
      R = true;
    }
  }
  if (max > 0 && nax > 0) {
    if (_nay > 0 && (position_.y - size_) > (WallPosition.y - WallSize.y / 2)) {
      //上にある
      U = true;
    }
    if (_may > 0 && (WallPosition.y + WallSize.y / 2) > (position_.y + size_)) {
      //下にある
      D = true;
    }
  }
  int add = 0;
  if (U) {
    position_.y = WallPosition.y + WallSize.y / 2 + (size_ + 1.0);
    velocity_.y *= -cofs_.ReflectCF * WallReflectionCF;
    // acceleration_.y_ *= -Cofs.ReflectCF * WallReflectionCF;
    acceleration_.y = 0;
    air_force_.y *= -cofs_.ReflectCF * WallReflectionCF;
    water_force_.y *= -cofs_.ReflectCF * WallReflectionCF;
    friction_force_.y *= -cofs_.ReflectCF * WallReflectionCF;
    IfOnWall();
  }
  if (D) {
    position_.y = WallPosition.y - WallSize.y / 2 - (size_ + 1.0);
    velocity_.y *= -cofs_.ReflectCF * WallReflectionCF;
    // acceleration_.y_ *= -Cofs.ReflectCF * WallReflectionCF;
    acceleration_.y = 0;
    air_force_.y *= -cofs_.ReflectCF * WallReflectionCF;
    water_force_.y *= -cofs_.ReflectCF * WallReflectionCF;
    friction_force_.y *= -cofs_.ReflectCF * WallReflectionCF;
    IfOnWall();
  }
  if (R) {
    position_.x = WallPosition.x - WallSize.x / 2 - (size_ + 1.0);
    velocity_.x *= -cofs_.ReflectCF * WallReflectionCF;
    // acceleration_.x_ *= -Cofs.ReflectCF * WallReflectionCF;
    acceleration_.x = 0;
    air_force_.x *= -cofs_.ReflectCF * WallReflectionCF;
    water_force_.x *= -cofs_.ReflectCF * WallReflectionCF;
    friction_force_.x *= -cofs_.ReflectCF * WallReflectionCF;
    IfOnWall();
  }
  if (L) {
    position_.x = WallPosition.x + WallSize.x / 2 + (size_ + 1.0);
    velocity_.x *= -cofs_.ReflectCF * WallReflectionCF;
    // acceleration_.x_ *= -Cofs.ReflectCF * WallReflectionCF;
    acceleration_.x = 0;
    air_force_.x *= -cofs_.ReflectCF * WallReflectionCF;
    water_force_.x *= -cofs_.ReflectCF * WallReflectionCF;
    friction_force_.x *= -cofs_.ReflectCF * WallReflectionCF;
    IfOnWall();
  }
  is_locked_axis_ = ((U | D) << 1) | (R | L);
  return (U | D) << 1 | (R | L);
}
