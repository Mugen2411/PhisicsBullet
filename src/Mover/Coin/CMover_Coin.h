#pragma once
#include "Effect/CEffectParent.h"
#include "Effect/CEffect_CoinDelete.h"
#include "Effect/CEffect_MoneyNumber.h"
#include "Mover/CMover.h"
#include "Mover/CMover_Player.h"
#include "Sound/CSoundManager.h"

class CMover_Coin : public CMover {
 public:
  enum Type {
    kBronze1,
    kBronze5,
    kSilver1e1,
    kSilver5e1,
    kGold1e2,
    kGold5e2,
    kPlatinum1e3,
    kPlatinum5e3,
    kRed1e4,
    kRed5e4,
    kOrange1e5,
    kOrange5e5,
    kYellow1e6,
    kYellow5e6,
    kGreen1e7,
    kGreen5e7,
    kCyan1e8,
    kCyan5e8,
    kBlue1e9,
    kBlue5e9,
    kViolet1e10,
    kViolet5e10,
    kRainbow1e11,
    kRainbow5e11,
    kBlack1e12
  };
  CMover_Coin(CVector position, Type type);

  static const double kValue[26];

  int Update();
  void Render() const;

  void Dead() {
    if (med_) {
      med_->GetMoney(kValue[type_]);
      CSoundManager::GetIns().Find("money")->Play(CSound::PlayType::kBack);
      CEffectParent::RegisterEffect(std::make_shared<CEffect_MoneyNumber>(
          position_ - CVector(0.0, size_), kValue[type_]));
      CEffectParent::RegisterEffect(std::make_shared<CEffect_CoinDelete>(
          position_, kSize[type_] / 12.0f, type_));
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
  static const double kSize[25];
  static const double kMass[25];
  Type type_;
  double animation_cnt_ = 0.0;
  double z;
  double dz;
};