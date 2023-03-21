#pragma once
#include "CEffectParent.h"
#include "CEffect_MoneyNumber.h"
#include "CMover.h"
#include "CMover_Player.h"
#include "CSoundManager.h"
#include "CEffect_CoinDelete.h"

class CMover_Coin : public CMover {
 public:
  enum Type { kBronze1, kSilver10, kGold100, kPlatinum1000, kRainbow10000 };
  CMover_Coin(CVector position, Type type);

  static const int kValue[6];

  int Update();
  void Render() const;

  void Dead() {
    if (med_) {
      med_->GetMoney(kValue[type_]);
      CSoundManager::GetIns().Find("money")->Play(CSound::PlayType::kBack);
      CEffectParent::RegisterEffect(std::make_shared<CEffect_MoneyNumber>(
          position_ - CVector(0.0, size_), kValue[type_]));
      CEffectParent::RegisterEffect(std::make_shared<CEffect_CoinDelete>(
          position_, kSize[type_] / 32.0f, type_));
    }
  };
  void Disappear(){};

  void Damage(CAttribute shotATK, int style){};
  void RatioDamage(CAttribute shotATK, int style) { status_ = kDead; };
  CAttribute TestDamage(CAttribute shotATK) { return shotATK; };

  void HitDispatch(std::shared_ptr<CMover> m) { m->Hit(this); }
  void Hit(CMover_Player* m) { status_ = kDead; }

  void BaseUpdate(){};
  bool BaseRender() const { return true; };
  void FieldDispatch(CField* f) {}

 protected:
  static const double kSize[5];
  static const double kMass[5];
  Type type_;
  double animation_cnt_ = 0.0;
  double z;
  double dz;
};