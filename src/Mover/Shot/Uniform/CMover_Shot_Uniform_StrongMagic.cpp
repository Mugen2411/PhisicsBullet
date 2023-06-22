#include "CMover_Shot_Uniform_StrongMagic.h"

#include "Effect/CEffect_Bright.h"
#include "Graphic/Image/CImageManager.h"

CMover_Shot_Uniform_StrongMagic::CMover_Shot_Uniform_StrongMagic(
    CAttribute baseATK, CVector position, double angle)
    : CMover_ShotBase("S_Uniform_Strong", baseATK, position, CVector(angle) * 6.0) {}

int CMover_Shot_Uniform_StrongMagic::Update() { return status_; }

void CMover_Shot_Uniform_StrongMagic::Render() const {
  CEffect_Bright::GetIns().Register(
      CEffect_Bright::BrightDesc(position_, 72, 192));
  CImageManager::GetIns()
      .Find("shot_uniform_strongmagic")
      ->DrawRotaF(position_, velocity_.GetAngle(), 1,
                  Constant::kPriorityShot);
}
