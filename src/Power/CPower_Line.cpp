#include "CPower_Line.h"

#include "Effect/CEffectParent.h"
#include "Effect/CEffect_Wind.h"
#include "Graphic/Image/CImageManager.h"

CPower_Line::CPower_Line(CVector position, CVector direction, double width,
                         double power, CAttribute damage, int duration)
    : CPower(position, power, damage, duration),
      direction_(direction),
      width_(width),
      damage_interval_(0) {
  corner_[0].x_ = position_.x_ + cos(direction.x_ - Constant::kPI / 2) * width / 2;
  corner_[0].y_ = position_.y_ + sin(direction.x_ - Constant::kPI / 2) * width / 2;
  corner_[1].x_ = position_.x_ + cos(direction.x_ + Constant::kPI / 2) * width / 2;
  corner_[1].y_ = position_.y_ + sin(direction.x_ + Constant::kPI / 2) * width / 2;
  corner_[2].x_ = position_.x_ + cos(direction.x_) * direction.y_ +
                 cos(direction.x_ + Constant::kPI / 2) * width / 2;
  corner_[2].y_ = position_.y_ + sin(direction.x_) * direction.y_ +
                 sin(direction.x_ + Constant::kPI / 2) * width / 2;
  corner_[3].x_ = position_.x_ + cos(direction.x_) * direction.y_ +
                 cos(direction.x_ - Constant::kPI / 2) * width / 2;
  corner_[3].y_ = position_.y_ + sin(direction.x_) * direction.y_ +
                 sin(direction.x_ - Constant::kPI / 2) * width / 2;

  force_direction_.x_ = cos(direction.x_);
  force_direction_.y_ = sin(direction.x_);
}

bool CPower_Line::isHit(CVector mPosition, double size) {
  //���_�Ƃ̓����蔻��
  for (int i = 0; i < 4; i++) {
    CVector dist(mPosition - corner_[i]);
    if (dist.GetLength2() < size * size) return true;
  }

  //�����̓����蔻��
  {
    CVector A = corner_[1] - corner_[0];
    CVector B = mPosition - corner_[0];
    double th1 = atan2(A.Cross(B), A.Dot(B));
    A = corner_[3] - corner_[2];
    B = mPosition - corner_[2];
    double th2 = atan2(A.Cross(B), A.Dot(B));
    if (0.0 <= th1 && th1 <= Constant::kPI / 2 && 0.0 <= th2 &&
        th2 <= Constant::kPI / 2)
      return true;
  }

  //�ӂƂ̓����蔻��
  for (int i = 0; i < 4; i++) {
    CVector A = corner_[i] - mPosition;
    CVector D = corner_[(i + 1) % 4] - corner_[i];
    double t = -D.Dot(A) / D.GetLength2();
    if (t < 0) t = 0;
    if (t > 1) t = 1;
    CVector T = corner_[i] + D * t;
    if ((mPosition - T).GetLength() < size) return true;
  }

  return false;
}

void CPower_Line::ApplyForceToMover(CMover* m) {
  if (isHit(m->GetPosition(), m->GetSize())) {
    m->ApplyAirForce(
        force_direction_ * power_ /
        ((m->GetPosition() - position_).GetLength() / direction_.y_));
    if (damage_interval_ == 0) {
      m->Damage(
          damage_ / 3 /
              max(0.05, min(1.0, ((m->GetPosition() - position_).GetLength() /
                                 direction_.y_))),
          1);
    }
  }
}

int CPower_Line::Update() {
  cnt_++;
  if (cnt_ > duration_) return 1;
  damage_interval_++;
  damage_interval_ %= 20;
  return 0;
}

void CPower_Line::Render() const {
  for (int i = 0; i < 3; i++) {
    CEffectParent::RegisterEffect(std::make_shared<CEffect_Wind>(
        power_ >= 0.0 ? position_ : position_ + CVector(direction_.x_)*direction_.y_, power_,
        (float)direction_.x_, width_, direction_.y_));
  }
}