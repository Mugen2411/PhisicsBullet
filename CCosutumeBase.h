#pragma once
#include "CAttribute.h"
#include "CStatus.h"
#include <string>
#include <memory>
#include "CMover_ShotBase.h"
#include "CSTGInputManager.h"

class CMover_Player;

class CCostumeBase
{
protected:
	CMover_Player* p_player;	//�v���C���[�ւ̃|�C���^
	std::string GraphFilePath;	//�摜�t�@�C���̃p�X

public:
	CAttribute AttributeDEF;	//�����ϐ�
	COF constants;				//�e�함���萔
	const double Mass;
	const double animSpeed;			//���t���[��������
	const int MaxCharge;				//���ߎˌ��ɕK�v�Ȏ���(���t���[��+1)
	const int ShotRate;				//�A�˂����t���[�����ƂɌ���
	const int StrongShotDuration;		//���U������������ɑ���s�\�ɂȂ�t���[����
	const double MaxSpeed;
	const double Accelaration;
	const std::string GID;

	CCostumeBase(std::string filepath, double animSpeed, int MaxCharge, int ShotRate,
		int strongshotDuration, double maxSpeed, double accel, double mass, CAttribute attrDEF, COF constants, std::string GID);
	virtual ~CCostumeBase(){}

	virtual void ChargeShot(double baseATK, CVector position, float angle) = 0;
	virtual void WeakShot(double baseATK, CVector position, float angle) = 0;

	void setPlayer(CMover_Player* p) {
		p_player = p;
	}
	void RegisterShot(std::shared_ptr<CMover_ShotBase>);

	virtual CCostumeBase* Clone() = 0;
};

