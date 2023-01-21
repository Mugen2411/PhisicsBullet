#pragma once
#include <random>

#include "CAttribute.h"
#include "CMover.h"
#include "CStatus.h"

class CField;

class CMover_EnemyBase : public CMover {
 public:
  CMover_EnemyBase(double Mass, int Level, double atkCF, double hpCF,
                   CAttribute attrDEF, int baseMoney, int color,
                   CVector Position, double accel, double maxSpeed, COF cofs);
  virtual ~CMover_EnemyBase() {}

  int state = -1;  //-1:出現中, 0:棒立ち, 1:移動, 2:怯み, それ以降は敵ごとに定義

  double Accel;
  double MaxSpeed;
  int baseMoney;

  int pushed;

  int Direction;
  double animCount;

  CStatus baseParams;  //基礎ステータス(HP・攻撃力・防御力)
  CAttribute attrDEF;  //属性耐性(なんかいっぱい)

  int Color;

  std::list<CVector> route;

  virtual void Walk(CVector destination);
  virtual void Move_on_Route();
  void Find_Route(int distance);
  void findTargetByDistance(int distance);

  void BaseUpdate();
  bool BaseRender() const;
  virtual int Update() = 0;
  virtual void Render() const = 0;
  virtual void Dead();
  virtual void Disappear();
  void onWall(CField* f, double WallReflectCF);

  void Render_HPGuage() const;

  void Damage(CAttribute shotATK, int style);
  void RatioDamage(CAttribute shotATK, int style);
  CAttribute TestDamage(CAttribute shotATK) { return shotATK / attrDEF; }
  void Drop();
  int DamageColor(CAttribute shotATK);

  virtual void FieldDispatch(CField* f) {}

  inline void HitDispatch(std::shared_ptr<CMover> m) { m->Hit(this); }
  void Hit(CMover_EnemyBase*);
  void Hit(CMover_Player*);

  virtual CMover_EnemyBase* Clone(CVector Position, int Level) = 0;

 protected:
  std::random_device seed;
  std::default_random_engine rand;
};
