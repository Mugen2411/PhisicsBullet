#include "CMover_Player.h"

#include <DxLib.h>

#include <cmath>

#include "CAnchor.h"
#include "CCostume_Festa.h"
#include "CCostume_Uniform.h"
#include "CEffectParent.h"
#include "CEffect_DamageNumber.h"
#include "CField.h"
#include "CImageManager.h"
#include "CSoundManager.h"

CMover_Player::CMover_Player(CVector position, int level, CCostumeBase* costume)
    : CMover(kPlayer, position, 24.0, CVector(0.0, 0.0), costume->mass_,
             costume->cofs_, 0),
      animation_cnt_(0.0),
      input_(CControllerFactory::GetIns().GetController()),
      direction_(1),
      charge_(0),
      state_(0),
      base_params_(level, 1.0, CPassiveSkill::GetIns().GetMaxHPmult()),
      digitHP_((int)std::log10(base_params_.maxHP_) + 1),
      wait_duration_(0),
      costume_(std::shared_ptr<CCostumeBase>(costume)),
      number_drawer_(),
      shot_wait_(0),
      heal_wait_(0) {
  costume->SetPlayer(this);
}

void CMover_Player::Walk() {
  CVector v = input_.lock()->GetVector();
  if (v.GetLength2() < Constant::kZeroBorder) return;
  CVector a =
      v * costume_->max_speed_ * CPassiveSkill::GetIns().GetSpeedMult() -
      velocity_;
  if (a.GetLength() > costume_->accel_) a = a.GetNorm() * costume_->accel_;
  if (velocity_.GetLength() < Constant::kDynamicBorder) {
    acceleration_ += a * sqrtl(now_fricted_ * cofs_.FrictionCF) *
                     sqrtl(1 - (now_water_forced_ * cofs_.WaterResCF));
  } else {
    acceleration_ += a * (now_fricted_ * cofs_.FrictionCF) *
                     (1 - (now_water_forced_ * cofs_.WaterResCF));
  }
}

void CMover_Player::BaseUpdate() {}

bool CMover_Player::BaseRender() const { return true; }

int CMover_Player::Update() {
  auto p = CAnchor::GetIns().GetAnchoredPosition(position_);
  if (p.x_ < Constant::kScrollMargin)
    CAnchor::GetIns().SetPosition(
        CVector(position_.x_ - Constant::kScrollMargin,
                CAnchor::GetIns().GetAnchorY()));
  if (p.x_ > Constant::kScreenW - Constant::kScrollMargin)
    CAnchor::GetIns().SetPosition(
        CVector(position_.x_ - Constant::kScreenW + Constant::kScrollMargin,
                CAnchor::GetIns().GetAnchorY()));

  if (p.y_ < Constant::kScrollMargin)
    CAnchor::GetIns().SetPosition(
        CVector(CAnchor::GetIns().GetAnchorX(),
                position_.y_ - Constant::kScrollMargin));
  if (p.y_ > Constant::kScreenH - Constant::kScrollMargin)
    CAnchor::GetIns().SetPosition(
        CVector(CAnchor::GetIns().GetAnchorX(),
                position_.y_ - Constant::kScreenH + Constant::kScrollMargin));

  if (state_ == 1) {
    wait_duration_--;
    if (wait_duration_ == 0) state_ = 0;
    return 0;
  }
  if (input_.lock()->IsChanged() > 0) {
    direction_ = input_.lock()->GetDirection();
    animation_cnt_ += costume_->animation_speed_;
    if (animation_cnt_ > 3.0) animation_cnt_ = 0.0;
  } else {
    animation_cnt_ = 0.0;
  }
  heal_wait_++;
  if (heal_wait_ == Constant::kFrame) {
    RatioHeal();
    heal_wait_ = 0;
  }
  Shot();
  Walk();
  return 0;
}

void CMover_Player::Shot() {
  float angle = input_.lock()->GetMouseAngle(
      CAnchor::GetIns().GetAnchoredPosition(position_));
  int LPushTime = input_.lock()->LClick(true);
  if (LPushTime == 0) {
    charge_ += CPassiveSkill::GetIns().GetChargeMult();
    charge_ = min(costume_->max_charge_, charge_);
    return;
  }
  if (charge_ < 0) return;
  if (charge_ == costume_->max_charge_) {
    costume_->ChargeShot(
        CPassiveSkill::GetIns().GetAtkMult() * base_params_.atk_,
        position_ + CVector(angle) * 16.0f, angle);
    shot_wait_ = 0;
    Wait(costume_->strong_shot_duration_);
    return;
  }
  if (shot_wait_ > costume_->shot_rate_) {
    shot_wait_ = 0;
    costume_->WeakShot(CPassiveSkill::GetIns().GetAtkMult() * base_params_.atk_,
                       position_ + CVector(angle) * 16.0f, angle);
  }
  shot_wait_++;
}

void CMover_Player::Render() const {
  CImageManager::GetIns()
      .Find(costume_->gid_)
      ->DrawRota(position_, 0.0f, 1.0f, 0,
                 direction_ * 4 + (uint32_t)std::round(animation_cnt_));
  auto anchored = CAnchor::GetIns().GetAnchoredPosition(position_);
  CAnchor::GetIns().EnableAbsolute();
  CImageManager::GetIns().Find("HPGuage")->DrawRotaFwithBlend(
      16 + 160, 16 + 8, 0, 1, 0xFFFFFF, DX_BLENDMODE_ALPHA, 108,
      Constant::kPriorityUI + 4, 2);
  CImageManager::GetIns().Find("HPGuage")->DrawRectwithBlend(
      16, 8, int(320 * (base_params_.HP_ / base_params_.maxHP_)), 32, 0xffffff,
      DX_BLENDMODE_ALPHA, 192, Constant::kPriorityUI + 5, 1);
  CImageManager::GetIns().Find("HPGuage")->DrawRotaFwithBlend(
      16 + 160, 16 + 8, 0, 1, 0xFFFFFF, DX_BLENDMODE_ALPHA, 255,
      Constant::kPriorityUI + 6, 0);
  number_drawer_.Draw(16 + 160, 16 + 8, base_params_.HP_, 0, 0,
                      Constant::kPriorityUI + 7);
  CImageManager::GetIns().Find("aim")->DrawCircleGauge(
      input_.lock()->MouseX(), input_.lock()->MouseY(),
      (double)charge_ / costume_->max_charge_, Constant::kPriorityUI + 7, 2);
  CImageManager::GetIns().Find("aim")->DrawRota(
      input_.lock()->MouseX(), input_.lock()->MouseY(), 0.0, 1.0,
      Constant::kPriorityUI + 7, (costume_->max_charge_ == charge_) ? 1 : 0);
  CVector diff = CVector((input_.lock()->MouseX() - anchored.x_) / 9.0,
                         (input_.lock()->MouseY() - anchored.y_) / 9.0);
  for (int i = 1; i < 9; i++) {
    CImageManager::GetIns().Find("aim")->DrawRotaFwithBlend(
        (int)(anchored.x_ + diff.x_ * i), (int)(anchored.y_ + diff.y_ * i), 0.0,
        1.0, 0xFFFFFF, CImageManager::BlendMode::kAlpha, 0x7F,
        Constant::kPriorityUI + 7, (costume_->max_charge_ == charge_) ? 4 : 3);
  }
  CAnchor::GetIns().DisableAbsolute();
}

void CMover_Player::Dead() {}

void CMover_Player::Disappear() {}

void CMover_Player::Wait(int duration) {
  state_ = 1;
  wait_duration_ = duration;
}

void CMover_Player::Damage(CAttribute BulletATK, int style) {
  double ret = ((BulletATK) / costume_->attribute_def_ *
                CPassiveSkill::GetIns().GetDefMult() * 0.01)
                   .Sum();
  if (ret < Constant::kZeroBorder) return;
  base_params_.HP_ -= ret;
  CSoundManager::GetIns().Find("player_hit")->Play(CSound::PlayType::kBack);
  CEffectParent::RegisterEffect(std::make_shared<CEffect_DamageNumber>(
      position_ - CVector(0.0, size_), ret, DamageColor(BulletATK), style));
}

void CMover_Player::RatioDamage(CAttribute BulletATK, int style) {
  double ret =
      ((BulletATK * base_params_.maxHP_) /
       (costume_->attribute_def_ * CPassiveSkill::GetIns().GetDefMult() * 100))
          .Sum();
  if (ret < Constant::kZeroBorder) return;
  base_params_.HP_ -= ret;
  CSoundManager::GetIns().Find("player_hit")->Play(CSound::PlayType::kBack);
  CEffectParent::RegisterEffect(std::make_shared<CEffect_DamageNumber>(
      position_ - CVector(0.0, size_), ret, DamageColor(BulletATK), style));
}

void CMover_Player::RatioHeal() {
  double diff = base_params_.maxHP_ * CPassiveSkill::GetIns().GetHealRatio();
  if (diff < Constant::kZeroBorder) return;
  base_params_.HP_ = (std::min)(base_params_.HP_ + diff, base_params_.maxHP_);
  CEffectParent::RegisterEffect(std::make_shared<CEffect_DamageNumber>(
      position_ - CVector(0.0, size_), diff, 3, 0));
}

int CMover_Player::DamageColor(CAttribute shotATK) {
  auto real = shotATK / costume_->attribute_def_;
  if (real.Sum() - shotATK.Sum() > Constant::kZeroBorder) return 1;
  if (real.Sum() - shotATK.Sum() < -Constant::kZeroBorder) return 2;
  return 0;
}

void CMover_Player::RegisterShot(std::shared_ptr<CMover_ShotBase> s) {
  med_->RegisterMover(s);
}

void CMover_Player::RegisterPower(std::shared_ptr<CPower> p) {
  med_->RegisterPower(p);
}

void CMover_Player::Hit(CMover_EnemyBase* m) {
  m->ApplyForce(acceleration_ * 0.1 * mass_);
  CVector delta = (m->GetPosition() - position_).GetLength2() < 4
                      ? CVector(GetRand(10) - 5, GetRand(10) - 5) * 0.02
                      : CVector(0.0, 0.0);
  m->ApplyForce((m->GetPosition() - position_ + delta).GetNorm() * mass_);
}

void CMover_Player::FieldDispatch(CField* f) {}