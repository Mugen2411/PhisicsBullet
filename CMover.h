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
  }  //力をかける
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

    //摩擦と水の抵抗と空気抵抗で静止する
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
  virtual bool BaseRender() const = 0;  //画面内ならtrueを返す
  virtual int Update() = 0;             // 0:生存　1:他殺 2:自殺
  virtual void Render() const = 0;
  virtual void Hit(CMover*);
  virtual void Hit(CMover_ShotBase*);
  virtual void Hit(CMover_BulletBase*);
  virtual void Hit(CMover_EnemyBase*);
  virtual void Hit(CMover_Player*);
  virtual void Dead() = 0;       //死亡(他殺)
  virtual void Disappear() = 0;  //消滅(自殺)

  virtual void Damage(CAttribute shotATK,
                      int style) = 0;  //ダメージを受ける処理
  virtual void RatioDamage(CAttribute shotATK,
                           int style) = 0;  //割合ダメージを受ける処理
  virtual CAttribute TestDamage(CAttribute shotATK) = 0;  //ダメージをテストする

  bool OnWall(CField* f,
              double WallReflectionCF);  //壁の上に乗ったか判定し、反射する
  virtual void IfOnWall(){};

 protected:
  CGameMediator* med_;

  CVector position_;      //座標
  CVector velocity_;      //速度
  CVector acceleration_;  //加速度

  double mass_;              //質量
  double now_fricted_;       //現在受けている摩擦系数
  double now_water_forced_;  //同じく水の抵抗
  COF cofs_;                 //各種定数
  double temperature_;       //温度

  CVector friction_force_;  //静止をシミュレートするために一時保存する摩擦力
  CVector water_force_;  //同じく水の抵抗
  CVector air_force_;    //同じく空気抵抗

  double size_;  //物体の大きさ(半径)

  int category_;  // MOVER_IDによってカテゴリ分け
  int status_;    // 0:生存　1:他殺 2:自殺

  int is_locked_axis_;  //(X固定)(Y固定)
};
