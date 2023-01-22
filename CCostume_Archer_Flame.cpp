#include "CCostume_Archer_Flame.h"

#include "CMover_Shot_Archer_FlameArrow.h"
#include "CMover_Shot_Archer_PlaneArrow.h"
#include "CSoundManager.h"

CCostume_Archer_Flame::CCostume_Archer_Flame(std::string gid_)
    : CCostumeBase("media/graphic/character/komuk/costume/archer/flame.png",
                   0.15, 40, 24, 10, 4.0, 2.0, 18.0,
                   CAttribute(1.0).Fire(1.5).Aqua(0.6),
                   COF(0.7, 0.97, 0.05, 0.0), gid_) {
  detail_ = CTextDrawer::Text(
      "�Α����̋|�𑀂�A�[�`���[�ߑ��B\n�퓬�ɓK���Ă��葫�����������ɂ߂��ۂ�"
      "�ア�B\n�A�˂͕��ʂ̋|�B�����₷���B\n���˂͉Α�����Z�����|��3���B"
      "\n�Η͂��ƂĂ������B",
      Constant::kCostumeDetailPosition, 0xFFFFFF, 0x000000, 0);
}

void CCostume_Archer_Flame::WeakShot(CAttribute baseATK, CVector position_,
                                     float angle) {
  CSoundManager::GetIns().Find("throw")->Play(CSound::PlayType::kBack);
  RegisterShot(std::make_shared<CMover_Shot_Archer_PlaneArrow>(
      baseATK, position_, angle));
}

void CCostume_Archer_Flame::ChargeShot(CAttribute baseATK, CVector position_,
                                       float angle) {
  CSoundManager::GetIns().Find("throw")->Play(CSound::PlayType::kBack);
  CSoundManager::GetIns().Find("little_fire")->Play(CSound::PlayType::kBack);
  for (int i = -1; i < 2; i++) {
    RegisterShot(std::make_shared<CMover_Shot_Archer_FlameArrow>(
        baseATK, position_, angle + i * Constant::kPI / 24));
  }
}
