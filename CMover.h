#pragma once
#include <memory>

#include "CAttribute.h"
#include "CGameMediator.h"
#include "CStatus.h"
#include "CVector.h"
#include "Constant.h"

class CMover_ShotBase;
class CMover_EnemyBase;
class CMover_BulletBase;
class CMover_Player;
class CField;

class CMover {
  friend CMoverParent;

 public:
  enum MoverID { kPlayer, kEnemy, kShot, kBullet };
  enum Status { kAlive = 0, kDead, kVanished };

  CMover(MoverID ID, CVector position, double size, CVector velocity,
         double mass, COF cofs, double temperature);
  virtual ~CMover(){};
  inline void SetMediator(CGameMediator* m) { med_ = m; }
  inline CVector GetPosition() { return position_; }
  inline void SetPosition(CVector pos) { position_ = pos; }
  inline CVector GetVelocity() { return velocity_; }
  inline CVector GetAcceleration() { return acceleration_; }
  inline double GetSize() { return size_; }
  inline int GetCategory() { return category_; }
  inline void SetStatus(int status) { status_ = status; }
  inline int GetStatus() { return status_; }
  inline void ApplyForce(CVector F) {
    acceleration_ += (F / mass_);
  }  //�͂�������
  inline void ApplyFrictionForce(double FloorFrictionCF) {
    now_fricted_ = FloorFrictionCF;
    auto NormA = velocity_;
    double cons = cofs_.FrictionCF * FloorFrictionCF * Constant::kGravity;
    friction_force_ = (NormA * -cons);
  }
  inline void ApplyAirRegistance(double FloorAirCF) {
    auto NormA = velocity_;
    air_force_ = (-NormA * cofs_.AirResCF * FloorAirCF);
  }
  inline void ApplyAirForce(CVector F) { ApplyForce(F * cofs_.AirResCF); }
  inline void ApplyWaterRegistance(double waterResCF) {
    now_water_forced_ = waterResCF;
    auto NormA = velocity_;
    water_force_ = (-NormA * cofs_.WaterResCF * waterResCF);
  }
  inline void ApplyWaterForce(CVector F) { ApplyForce(F * cofs_.WaterResCF); }
  inline void Move() {
#ifdef _DEBUG
    if (category_ == MoverID::kPlayer) {
      printfDx("SP:%lf,%lf\nAP:%lf,%lf\n", velocity_.x_, velocity_.y_,
               acceleration_.x_, acceleration_.y_);
      printfDx("Fric:%lf\nWtr:%lf\nAir:%lf\n", friction_force_.GetLength(),
               water_force_.GetLength2(), air_force_.GetLength());
    }
#endif

    //���C�Ɛ��̒�R�Ƌ�C��R�ŐÎ~����
    /*CVector frictedVelocity = velocity_ + friction_force_;
    if (frictedVelocity.Dot(velocity_) < 0) frictedVelocity = CVector(0.0, 0.0);

    CVector wateredVelocity = velocity_ + water_force_;
    if (wateredVelocity.Dot(velocity_) < 0) wateredVelocity = CVector(0.0, 0.0);

    CVector airedVelocity = velocity_ + air_force_;
    if (airedVelocity.Dot(velocity_) < 0) airedVelocity = CVector(0.0, 0.0);

    if (frictedVelocity.GetLength2() < Constant::kZeroBorder ||
        wateredVelocity.GetLength2() < Constant::kZeroBorder ||
        airedVelocity.GetLength2() < Constant::kZeroBorder) {
      velocity_ = CVector(0.0, 0.0);
    } else*/
    {
      acceleration_ += friction_force_;
      acceleration_ += water_force_;
      acceleration_ += air_force_;
    }

    velocity_ += acceleration_ * sqrtl(Constant::kPerFrame);

    if (velocity_.GetLength2() > 32 * 32) {
      velocity_ = velocity_.GetNorm() * 32;
    }

    if (!(is_locked_axis_ & 1)) {
      position_.x_ += velocity_.x_;
    }
    if (!((is_locked_axis_ >> 1) & 1)) {
      position_.y_ += velocity_.y_;
    }
    ResetPower();
  }

  void ResetPower() {
    is_locked_axis_ = 0;
    acceleration_.x_ = 0;
    acceleration_.y_ = 0;
    friction_force_ = CVector(0.0, 0.0);
    water_force_ = CVector(0.0, 0.0);
    air_force_ = CVector(0.0, 0.0);
    velocity_.Zero();
  }

  virtual void HitDispatch(std::shared_ptr<CMover> m) = 0;
  virtual void FieldDispatch(CField* f) = 0;

  virtual void BaseUpdate() = 0;
  virtual bool BaseRender() const = 0;  //��ʓ��Ȃ�true��Ԃ�
  virtual int Update() = 0;             // 0:�����@1:���E 2:���E
  virtual void Render() const = 0;
  virtual void Hit(CMover*);
  virtual void Hit(CMover_ShotBase*);
  virtual void Hit(CMover_BulletBase*);
  virtual void Hit(CMover_EnemyBase*);
  virtual void Hit(CMover_Player*);
  virtual void Dead() = 0;       //���S(���E)
  virtual void Disappear() = 0;  //����(���E)

  virtual void Damage(CAttribute shotATK,
                      int style) = 0;  //�_���[�W���󂯂鏈��
  virtual void RatioDamage(CAttribute shotATK,
                           int style) = 0;  //�����_���[�W���󂯂鏈��
  virtual CAttribute TestDamage(CAttribute shotATK) = 0;  //�_���[�W���e�X�g����

  bool OnWall(CField* f,
              double WallReflectionCF);  //�ǂ̏�ɏ���������肵�A���˂���
  virtual void IfOnWall(){};

 protected:
  CGameMediator* med_;

  CVector position_;      //���W
  CVector velocity_;      //���x
  CVector acceleration_;  //�����x

  double mass_;              //����
  double now_fricted_;       //���ݎ󂯂Ă��門�C�n��
  double now_water_forced_;  //���������̒�R
  COF cofs_;                 //�e��萔
  double temperature_;       //���x

  CVector friction_force_;  //�Î~���V�~�����[�g���邽�߂Ɉꎞ�ۑ����門�C��
  CVector water_force_;  //���������̒�R
  CVector air_force_;    //��������C��R

  double size_;  //���̂̑傫��(���a)

  int category_;  // MOVER_ID�ɂ���ăJ�e�S������
  int status_;    // 0:�����@1:���E 2:���E

  int is_locked_axis_;  //(X�Œ�)(Y�Œ�)
};
