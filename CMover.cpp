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
  double max = (position_.x_ + size_) - (WallPosition.x_ - WallSize.x_ / 2),
         may = (position_.y_ + size_) - (WallPosition.y_ - WallSize.y_ / 2);
  double nax = (WallPosition.x_ + WallSize.x_ / 2) - (position_.x_ - size_),
         nay = (WallPosition.y_ + WallSize.y_ / 2) - (position_.y_ - size_);
  double _max = (nextPosition.x_ + size_) - (WallPosition.x_ - WallSize.x_ / 2),
         _may = (nextPosition.y_ + size_) - (WallPosition.y_ - WallSize.y_ / 2);
  double _nax = (WallPosition.x_ + WallSize.x_ / 2) - (nextPosition.x_ - size_),
         _nay = (WallPosition.y_ + WallSize.y_ / 2) - (nextPosition.y_ - size_);
  bool U = false, D = false, R = false, L = false;

  auto setU = [&]() {
    position_.y_ = WallPosition.y_ + WallSize.y_ / 2 + (size_ + 2.0);
  };
  auto setD = [&]() {
    position_.y_ = WallPosition.y_ - WallSize.y_ / 2 - (size_ + 2.0);
  };
  auto setR = [&]() {
    position_.x_ = WallPosition.x_ - WallSize.x_ / 2 - (size_ + 2.0);
  };
  auto setL = [&]() {
    position_.x_ = WallPosition.x_ + WallSize.x_ / 2 + (size_ + 2.0);
  };

  //カド同士の判定
  if (0 >= max && 0 >= may && _max > 0 && _may > 0) {
    if (_max >= _may) {
      //下にある
      D = true;
      setD();
    } else {
      //右にある
      R = true;
      setR();
    }
  }
  if (0 >= nax && 0 >= may && _nax > 0 && _may > 0) {
    if (_nax >= _may) {
      //下にある
      D = true;
      setD();
    } else {
      //左にある
      L = true;
      setL();
    }
  }
  if (0 >= max && 0 >= nay && _max > 0 && _nay > 0) {
    if (_max >= _nay) {
      //上にある
      U = true;
      setU();
    } else {
      //右にある
      R = true;
      setR();
    }
  }
  if (0 >= nax && 0 >= nay && _nax > 0 && _nay > 0) {
    if (_nax >= _nay) {
      //上にある
      U = true;
      setU();
    } else {
      //左にある
      L = true;
      setL();
    }
  }

  //上下左右の判定
  if (may > 0 && nay > 0) {
    if (_nax > 0 && (position_.x_ - size_) > (WallPosition.x_ - WallSize.x_ / 2)) {
      //左にある
      L = true;
      setL();
    }
    if (_max > 0 && (WallPosition.x_ + WallSize.x_ / 2) > (position_.x_ + size_)) {
      //右にある
      R = true;
      setR();
    }
  }
  if (max > 0 && nax > 0) {
    if (_nay > 0 && (position_.y_ - size_) > (WallPosition.y_ - WallSize.y_ / 2)) {
      //上にある
      U = true;
      setU();
    }
    if (_may > 0 && (WallPosition.y_ + WallSize.y_ / 2) > (position_.y_ + size_)) {
      //下にある
      D = true;
      setD();
    }
  }
  if (R || L) {
    velocity_.x_ *= -cofs_.ReflectCF * WallReflectionCF;
    // acceleration_.x_ *= -Cofs.ReflectCF * WallReflectionCF;
    acceleration_.x_ = 0;
    air_force_.x_ *= -cofs_.ReflectCF * WallReflectionCF;
    water_force_.x_ *= -cofs_.ReflectCF * WallReflectionCF;
    friction_force_.x_ *= -cofs_.ReflectCF * WallReflectionCF;
  }
  if (U || D) {
    velocity_.y_ *= -cofs_.ReflectCF * WallReflectionCF;
    // acceleration_.y_ *= -Cofs.ReflectCF * WallReflectionCF;
    acceleration_.y_ = 0;
    air_force_.y_ *= -cofs_.ReflectCF * WallReflectionCF;
    water_force_.y_ *= -cofs_.ReflectCF * WallReflectionCF;
    friction_force_.y_ *= -cofs_.ReflectCF * WallReflectionCF;
  }
  if (U || D || R || L) IfOnWall();
  int add = 0;
  is_locked_axis_ = ((U | D) << 1) | (R | L);
  return (U | D) << 1 | (R | L);
}
