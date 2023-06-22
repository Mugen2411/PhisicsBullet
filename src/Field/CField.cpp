#include "CField.h"

#include "Mover/Bullet/CMover_BulletBase.h"
#include "Mover/Shot/CMover_ShotBase.h"

CField::CField(std::string gid, CVector position_, CVector size, COF cofs,
               double temperature, CAttribute damage, bool is_wall_)
    : gid_(gid),
      position_(position_),
      size_(size),
      cofs_(cofs),
      temperature_(temperature),
      damage_(damage),
      damage_interval_(0),
      is_wall_(is_wall_) {}

void CField::SetFrictionForce(CMover* m) {
  m->ApplyFrictionForce(cofs_.FrictionCF);
  m->ApplyWaterRegistance(cofs_.WaterResCF);
  m->ApplyAirRegistance(cofs_.AirResCF);
  if (damage_interval_ == 0 || m->GetStatus() == CMover::Status::kDead) {
    m->FieldDispatch(this);
    CAttribute t = m->TestDamage(damage_);
    if (damage_.Sum() < t.Sum() || damage_.Sum() > 24.0 || (t.Sum() < 0.0 && damage_.Sum() != 0.0))
      m->RatioDamage(damage_ / 10.0, 1);
  }
  damage_interval_++;
  damage_interval_ %= 6;
}

void CField::Update() {}

void CField::Render() const {}

void CField::AttributeEffect(CMover_ShotBase* m) {
  AttributeReaction(m->GetBaseAttribute());
}

void CField::AttributeEffect(CMover_BulletBase* m) {
  AttributeReaction(m->GetBaseAttribute());
}

void CField::Save(std::ofstream& fout) { fout << gid_ << "\n"; }
