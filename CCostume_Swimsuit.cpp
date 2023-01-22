#include "CCostume_Swimsuit.h"

#include "CEffectParent.h"
#include "CEffect_Bat_Swing.h"
#include "CMover_Shot_Swimsuit_Bat.h"
#include "CMover_Shot_Swimsuit_iPhone.h"
#include "CSoundManager.h"

CCostume_Swimsuit::CCostume_Swimsuit(std::string gid_)
    : CCostumeBase("media/graphic/character/komuk/costume/swimsuit/komuk.png",
                   0.1, 60, 24, 30, 4.0, 2.0, 18.0,
                   CAttribute(0.9).Aqua(2.5).Fire(0.7).Thunder(0.5),
                   COF(0.6, 0.1, 0.05, 0.0), gid_) {
  detail_ = CTextDrawer::Text(
      "�N������̎�ō��ꂽ�X�N�[�������B\n�ǂ����Ă��퓬�ɂ͓K���Ă��Ȃ���"
      "\n�������ϐ����ւ�B\n�A�˂͌^������iPh�Zne�B\n�������̃_���[�W���܂ށB"
      "\n���˂͞��_�B�X�C�J�̑���ɓG�̓����J�`����B",
      Constant::kCostumeDetailPosition, 0xFFFFFF, 0x000000, 0);
}

void CCostume_Swimsuit::WeakShot(CAttribute baseATK, CVector position,
                                 float angle) {
  CSoundManager::GetIns().Find("throw")->Play(CSound::PlayType::kBack);
  player_ptr_->RegisterShot(
      std::make_shared<CMover_Shot_Swimsuit_iPhone>(baseATK, position, angle));
}

void CCostume_Swimsuit::ChargeShot(CAttribute baseATK, CVector position,
                                   float angle) {
  CSoundManager::GetIns().Find("bat_swing")->Play(CSound::PlayType::kBack);
  for (int i = 0; i < 8; i++) {
    player_ptr_->RegisterShot(std::make_shared<CMover_Shot_Swimsuit_Bat>(
        baseATK, position, angle, i * 2));
  }
  CEffectParent::RegisterEffect(
      std::make_shared<CEffect_Bat_Swing>(position, angle));
}