#include "CCostume_Uniform.h"
#include "CMover_Shot_Uniform_Homing.h"
#include "CMover_Shot_Uniform_StrongMagic.h"
#include "CSoundManager.h"

CCostume_Uniform::CCostume_Uniform(std::string GID) :
	CCostumeBase("media/graphic/character/komuk/costume/uniform/komuk.png", 0.1, 60, 12, 20, 3.5, 1.8, 20.0,
		CAttribute(1.0), COF(0.7, 0.96, 0.05, 0.0),GID) {
	detail = CTextDrawer::Text("�ŏ��ɗ��Ă��������B�ł���{�I�Ȉߑ��ł���A\n�S�Ă̑ϐ������ϓI�B\n�A�˂͗U�����@�e�B\n�ł��߂��G��T���čU������B\n�������ǂɓ�����Ə����Ă��܂��B\n���˂͍��o�͖��@�e�B\n���͂̊��̉e�����󂯂���\n�܂��������ō��߂̃_���[�W��^����B", Constant::Costume_detail_pos, 0xFFFFFF, 0x000000, 0);
}

void CCostume_Uniform::WeakShot(double baseATK, CVector position, float angle)
{
	CSoundManager::getIns().find("little_magic")->Play(CSound::PLAYTYPE::PT_BACK);
	RegisterShot(std::make_shared<CMover_Shot_Uniform_Homing>(baseATK, position, angle));
}

void CCostume_Uniform::ChargeShot(double baseATK, CVector position, float angle)
{
	CSoundManager::getIns().find("middle_magic")->Play(CSound::PLAYTYPE::PT_BACK);
	RegisterShot(std::make_shared<CMover_Shot_Uniform_StrongMagic>(baseATK, position, angle));
}
