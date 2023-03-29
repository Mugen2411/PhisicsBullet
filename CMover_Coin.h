#pragma once
#include "CEffectParent.h"
#include "CEffect_CoinDelete.h"
#include "CEffect_MoneyNumber.h"
#include "CMover.h"
#include "CMover_Player.h"
#include "CSoundManager.h"

class CMover_Coin : public CMover {
 public:
  enum Type {
    kBronze1,
    kBronze5,
    kSilver10,
    kSilver50,
    kGold100,
    kGold500,
    kPlatinum1000,
    kPlatinum5000,
    kRainbow10000,
    kRainbow50000,
    kBlack100000
  };
  CMover_Coin(CVector position, Type type);

  static const int kValue[12];

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
  static const double kSize[11];
  static const double kMass[11];
  Type type_;
  double animation_cnt_ = 0.0;
  double z;
  double dz;
};