#pragma once
#include <random>

#include "CAttribute.h"
#include "CMover.h"
#include "CStatus.h"

class CField;

class CMover_EnemyBase : public CMover {
 public:
  CMover_EnemyBase(std::string GID, int Level, CVector position);
  virtual ~CMover_EnemyBase() {}

  int state_ =
      -1;  //-1:oŒ»’†, 0:–_—§‚¿, 1:ˆÚ“®, 2:‹¯‚İ, ‚»‚êˆÈ~‚Í“G‚²‚Æ‚É’è‹`

  double accel_;
  double max_speed_;
  int base_money_;

  int pushed_;

  int direction_;
  double animation_cnt_;

  CStatus base_params_;  //Šî‘bƒXƒe[ƒ^ƒX(HPEUŒ‚—ÍE–hŒä—Í)
  CAttribute attr_def_;  //‘®«‘Ï«(‚È‚ñ‚©‚¢‚Á‚Ï‚¢)

  int color_;

  std::list<CVector> route_;

  virtual void Walk(CVector destination);
  virtual void Move_on_Route();
  void FindRoute(int distance);
  void FindTargetByDistance(int distance);

  void BaseUpdate();
  bool BaseRender() const;
  virtual int Update() = 0;
  virtual void Render() const = 0;
  virtual void Dead();
  virtual void Disappear();
  void OnWall(CField* f, double WallReflectCF);

  void Render_HPGuage() const;

  void Damage(CAttribute shotATK, int style);
  void RatioDamage(CAttribute shotATK, int style);
  CAttribute TestDamage(CAttribute shotATK) { return shotATK / attr_def_; }
  void Drop();
  int DamageColor(CAttribute shotATK);

  virtual void FieldDispatch(CField* f) {}

  inline void HitDispatch(std::shared_ptr<CMover> m) { m->Hit(this); }
  void Hit(CMover_EnemyBase*);
  void Hit(CMover_Player*);

  void LoadStatus(std::string GID, int Level);

  virtual CMover_EnemyBase* Clone(CVector position, int Level) = 0;

 protected:
  std::random_device seed_;
  std::default_random_engine rand_;
};
