#include "CCostume_Uniform.h"

#include "CMover_Shot_Uniform_Homing.h"
#include "CMover_Shot_Uniform_StrongMagic.h"
#include "CPower_Line.h"
#include "CSoundManager.h"

CCostume_Uniform::CCostume_Uniform(std::string gid_)
    : CCostumeBase("media/graphic/character/komuk/costume/uniform/komuk.png",
                   0.1, 60, 12, 20, 3.5, 1.8, 20.0, CAttribute(1.0).Aqua(0.98),
                   COF(0.7, 0.96, 0.05, 0.0), gid_) {
  detail_ = CTextDrawer::Text(
      "�ŏ��ɗ��Ă��������B�ł���{�I�Ȉߑ��ł���A\n�S�Ă̑ϐ������ϓI�B\n�A��"
      "�͗U�����@�e�B\n�ł��߂��G��T���čU������B\n�������ǂɓ�����Ə����Ă�"
      "�܂��B\n���˂͍��o�͖��@�e�B\n���͂̊��̉e�����󂯂���\n�܂���������"
      "���߂̃_���[�W��^����B",
      Constant::kCostumeDetailPosition, 0xFFFFFF, 0x000000, 0);
}

void CCostume_Uniform::WeakShot(CAttribute baseATK, CVector position_,
                                float angle) {
  CSoundManager::GetIns().Find("little_magic")->Play(CSound::PlayType::kBack);
  RegisterShot(
      std::make_shared<CMover_Shot_Uniform_Homing>(baseATK, position_, angle));
  // p_player->RegisterPower(std::make_shared<CPower_Line>(position_ +
  // CVector(angle_) * 32, CVector(angle_, 128.0), 64, 30, 1));
}

void CCostume_Uniform::ChargeShot(CAttribute baseATK, CVector position_,
                                  float angle) {
  CSoundManager::GetIns().Find("middle_magic")->Play(CSound::PlayType::kBack);
  RegisterShot(std::make_shared<CMover_Shot_Uniform_StrongMagic>(
      baseATK, position_, angle));
}
