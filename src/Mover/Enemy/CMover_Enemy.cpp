#include "CMover_Enemy.h"

#include "Calc/CPassiveSkill.h"
#include "Data/CDataLoader.h"
#include "Effect/CEffectParent.h"
#include "Effect/CEffect_DamageNumber.h"
#include "Effect/CEffect_EnemyDelete.h"
#include "Effect/CEffect_MoneyNumber.h"
#include "Graphic/CAnchor.h"
#include "Graphic/Image/CImageManager.h"
#include "Mover/CMover_Player.h"
#include "Mover/Coin/CMover_Coin.h"
#include "Sound/CSoundManager.h"

CMover_EnemyBase::CMover_EnemyBase(std::string GID, int Level, CVector position)
    : CMover(kEnemy, position, 24.0, CVector(0.0, 0.0), 0, COF(), 0),
      accel_(0),
      max_speed_(0),
      direction_(0),
      animCnt_(0.0, 0.0),
      base_params_(0, 0, 0),
      attr_def_(0),
      base_money_(0),
      color_(0),
      seed_(),
      rand_(seed_()),
      pushed_(0) {
  LoadStatus(GID, Level);
}

void CMover_EnemyBase::Walk(CVector destination) {
  CVector diff = (destination - position_).GetNorm() * max_speed_;
  CVector a = diff.GetNorm() * max_speed_ - velocity_;
  if (a.GetLength() > accel_) a = a.GetNorm() * accel_;
  if (velocity_.GetLength() < Constant::kDynamicBorder) {
    acceleration_ += a * sqrtl(now_fricted_ * cofs_.FrictionCF) *
                     sqrtl(1 - (now_water_forced_ * cofs_.WaterResCF));
  } else {
    acceleration_ += a * (now_fricted_ * cofs_.FrictionCF) *
                     (1 - (now_water_forced_ * cofs_.WaterResCF));
  }
  direction_ = diff.GetDirection();
}

void CMover_EnemyBase::Move_on_Route() {
  if (route_.empty()) {
    return;
  }
  if ((position_ - route_.front()).GetLength2() < 8 * 8) {
    route_.pop_front();
    return;
  }
  Walk(route_.front());
}

void CMover_EnemyBase::FindRoute(int distance) {
  if (!med_) return;
  route_ =
      med_->GetRoute(position_, med_->GetPlayerPosition(), attr_def_, distance);
}

void CMover_EnemyBase::FindTargetByDistance(int distance) {
  if (!med_) return;
  std::vector<CVector> dists =
      med_->GetTargetByDistance(med_->GetPlayerPosition(), distance);
  std::uniform_int_distribution<> r(0, (int)dists.size() - 1);
  CVector target = dists[r(rand_)];
  route_ = med_->GetRoute(position_, target, attr_def_, 0);
}

void CMover_EnemyBase::BaseUpdate() {
  pushed_ = 0;
  animCnt_.Update();
}

bool CMover_EnemyBase::BaseRender() const {
  /*for (auto& i : route_) {
          CImageManager::GetIns().Find("editor_cursor")->DrawRota(i.x_, i.y_, 0,
  1, 1.0);
  }*/
  auto p = CAnchor::GetIns().GetAnchoredPosition(position_);
  CAnchor::GetIns().EnableAbsolute();
  if (p.x_ + size_ < 0) {
    if (p.y_ + size_ < 0) {
      CImageManager::GetIns()
          .Find("enemy_marker")
          ->DrawRota(8, 8, (p - CVector(0, 0)).GetAngle(), 1.0,
                     Constant::kPriorityMarker);
      CAnchor::GetIns().DisableAbsolute();
      return false;
    }
    if (p.y_ - size_ > Constant::kScreenH) {
      CImageManager::GetIns()
          .Find("enemy_marker")
          ->DrawRota(8, Constant::kScreenH - 8,
                     (p - CVector(0, Constant::kScreenH)).GetAngle(), 1.0,
                     Constant::kPriorityMarker);
      CAnchor::GetIns().DisableAbsolute();
      return false;
    }
    CImageManager::GetIns()
        .Find("enemy_marker")
        ->DrawRota(8, (int)p.y_, (float)Constant::kPI, 1.0f,
                   Constant::kPriorityMarker);
    CAnchor::GetIns().DisableAbsolute();
    return false;
  }
  if (p.x_ - size_ > Constant::kScreenW) {
    if (p.y_ + size_ < 0) {
      CImageManager::GetIns()
          .Find("enemy_marker")
          ->DrawRota(Constant::kScreenW - 8, 8,
                     (p - CVector(Constant::kScreenW, 0)).GetAngle(), 1.0,
                     Constant::kPriorityMarker);
      CAnchor::GetIns().DisableAbsolute();
      return false;
    }
    if (p.y_ - size_ > Constant::kScreenH) {
      CImageManager::GetIns()
          .Find("enemy_marker")
          ->DrawRota(
              Constant::kScreenW - 8, Constant::kScreenH - 8,
              (p - CVector(Constant::kScreenW, Constant::kScreenH)).GetAngle(),
              1.0, Constant::kPriorityMarker);
      CAnchor::GetIns().DisableAbsolute();
      return false;
    }
    CImageManager::GetIns()
        .Find("enemy_marker")
        ->DrawRota(Constant::kScreenW - 8, (int)p.y_,
                   (float)Constant::kPI * 0.0f, 1.0f,
                   Constant::kPriorityMarker);
    CAnchor::GetIns().DisableAbsolute();
    return false;
  }
  if (p.y_ + size_ < 0) {
    CImageManager::GetIns()
        .Find("enemy_marker")
        ->DrawRota((int)p.x_, 8, -(float)Constant::kPI / 2, 1.0f,
                   Constant::kPriorityMarker);
    CAnchor::GetIns().DisableAbsolute();
    return false;
  }
  if (p.y_ - size_ > Constant::kScreenH) {
    CImageManager::GetIns()
        .Find("enemy_marker")
        ->DrawRota((int)p.x_, Constant::kScreenH - 8, (float)Constant::kPI / 2,
                   1.0f, Constant::kPriorityMarker);
    CAnchor::GetIns().DisableAbsolute();
    return false;
  }
  CAnchor::GetIns().DisableAbsolute();
  Render_HPGuage();
  return true;
}

void CMover_EnemyBase::Dead() {
  Drop();
  for (int i = 0; i < 5; i++)
    CEffectParent::RegisterEffect(std::make_shared<CEffect_EnemyDelete>(
        position_ + CVector(GetRand((int)size_ * 3) - size_ * 1.5,
                            GetRand((int)size_ * 3) - size_ * 1.5),
        size_ * 0.5 + GetRand((int)(size_ * 1.5)), color_, 30));
  for (int i = 0; i < 2; i++)
    CEffectParent::RegisterEffect(std::make_shared<CEffect_EnemyDelete>(
        position_, size_ * (4 + i * 1.0), color_, 12));

  CAnchor::GetIns().Quake(15, 3.0);
  CSoundManager::GetIns().Find("enemy_kill")->Play(CSound::kBack);
}

void CMover_EnemyBase::Disappear() {}

void CMover_EnemyBase::Render_HPGuage() const {
  CImageManager::GetIns()
      .Find("enemy_HPGuage")
      ->DrawExtendWithBlend(position_.x_ - 16, position_.y_ - size_ - 8,
                            position_.x_ + 16, position_.y_ - size_ - 4,
                            0xFFFFFF, DX_BLENDMODE_ALPHA, 108,
                            Constant::kPriorityMarker, 1);
  CImageManager::GetIns()
      .Find("enemy_HPGuage")
      ->DrawExtendWithBlend(
          position_.x_ - 16, position_.y_ - size_ - 8,
          position_.x_ - 16 + 32 * (base_params_.HP_ / base_params_.maxHP_),
          position_.y_ - size_ - 4, 0xFFFFFF, DX_BLENDMODE_ALPHA, 160,
          Constant::kPriorityMarker, 0);
}

void CMover_EnemyBase::Damage(CAttribute shotATK, int style) {
  if (status_ < 0) return;
  double ret = (shotATK / attr_def_ * 0.01).Sum();
  // if (ret < Constant::zero_border && ret > -Constant::zero_border)return;
  base_params_.HP_ -= ret;
  base_params_.HP_ = min(base_params_.HP_, base_params_.maxHP_);
  CEffectParent::RegisterEffect(std::make_shared<CEffect_DamageNumber>(
      position_ - CVector(0.0, size_), (ret < 0) ? -ret : ret,
      DamageColor(shotATK), style));
  CSoundManager::GetIns().Find("enemy_hit")->Play(CSound::PlayType::kBack);
  if (base_params_.HP_ < 0) {
    SetStatus(Status::kDead);
  }
}

void CMover_EnemyBase::RatioDamage(CAttribute shotATK, int style) {
  if (status_ < 0) return;
  double ret = ((shotATK * base_params_.maxHP_) / (attr_def_ * 100)).Sum();
  // if (ret < Constant::zero_border && ret > -Constant::zero_border)return;
  base_params_.HP_ -= ret;
  base_params_.HP_ = min(base_params_.HP_, base_params_.maxHP_);
  CEffectParent::RegisterEffect(std::make_shared<CEffect_DamageNumber>(
      position_ - CVector(0.0, size_), (ret < 0) ? -ret : ret,
      DamageColor(shotATK), style));
  if (base_params_.HP_ < 0) {
    SetStatus(Status::kDead);
  }
}

void CMover_EnemyBase::Drop() {
  double val = std::ceil(
      ((base_money_ + CPassiveSkill::GetIns().GetEnemyValueAdd()) *
                 powl(1.05, base_params_.level_) *
                 std::pow(1.28, (int)(base_params_.level_ / 15)) *
                 std::pow(1.72, (int)(base_params_.level_ / 60))) *
      CPassiveSkill::GetIns().GetMoneyMult());
  if (auto r = med_) {
    // r->GetMoney(val);
    for (int v = 0; CMover_Coin::kValue[v] > 0; v++) {
      while (val >= CMover_Coin::kValue[v]) {
        val -= CMover_Coin::kValue[v];
        med_->RegisterCoin(
            std::make_shared<CMover_Coin>(position_, (CMover_Coin::Type)v));
      }
    }
  }
  // CEffectParent::RegisterEffect(std::make_shared<CEffect_MoneyNumber>(
  //     position_ - CVector(0.0, size_), val));
}

int CMover_EnemyBase::DamageColor(CAttribute shotATK) {
  auto real = shotATK * attr_def_;
  if (real.Sum() < 0.0) return 3;
  if (real.Sum() - shotATK.Sum() > Constant::kZeroBorder) return 2;
  if (real.Sum() - shotATK.Sum() < -Constant::kZeroBorder) return 1;
  return 0;
}

void CMover_EnemyBase::Hit(CMover_EnemyBase* m) {
  pushed_++;
  CVector diff = m->GetPosition() - position_;
  CVector delta = diff.GetLength2() < Constant::kZeroBorder
                      ? CVector(Constant::kPI2 / 64 * GetRand(64))
                      : CVector(0.0, 0.0);
  m->ApplyForce((diff + delta).GetNorm() * mass_ / pushed_);
}

void CMover_EnemyBase::Hit(CMover_Player* m) {
  CVector diff = m->GetPosition() - position_;
  CVector delta = CVector(Constant::kPI2 / 64 * GetRand(64));
  m->ApplyForce((diff + delta).GetNorm() * mass_);
  m->ApplyForce(velocity_ * mass_);
}

void CMover_EnemyBase::LoadStatus(std::string GID, int Level) {
  auto d = CDataLoader::GetIns().Get("main")->GetChild("enemy");
  if (d == nullptr) {
    MessageBox(NULL, "error at enemy params", "CDataNode", MB_OK);
    abort();
  }
  auto e = d->GetChild(GID);
  base_money_ = e->GetChild("mny")->GetInt();
  mass_ = e->GetChild("mass")->GetInt();
  base_params_ =
      CStatus(Level, e->GetChild("base")->GetChild("atk")->GetDouble(),
              e->GetChild("base")->GetChild("hp")->GetDouble());
  max_speed_ = e->GetChild("spd")->GetDouble();
  animCnt_ = CAnimationCounter(4.0, e->GetChild("animSpd")->GetDouble());
  accel_ = e->GetChild("acl")->GetDouble();
  attr_def_.Load(e->GetChild("atrd"));
  cofs_.Load(e->GetChild("cof"));
  color_ = e->GetChild("effc")->GetInt();
}