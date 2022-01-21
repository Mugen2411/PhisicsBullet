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
	double animSpeed;			//���t���[��������
	int MaxCharge;				//���ߎˌ��ɕK�v�Ȏ���(���t���[��+1)
	int ShotRate;				//�A�˂����t���[�����ƂɌ���
	int StrongShotDuration;		//���U������������ɑ���s�\�ɂȂ�t���[����
	double MaxSpeed;
	double Accelaration;

public:
	CAttribute AttributeDEF;	//�����ϐ�
	double atkCF, defCF, hpCF;	//�e��{��

	CCostumeBase(CMover_Player* player, std::string filepath, double animSpeed, int MaxCharge, int ShotRate,
		int strongshotDuration, double maxSpeed, double accel, CAttribute attrDEF);

	virtual std::shared_ptr<CMover_ShotBase> ChargeShot(double baseATK, CVector position, float angle) = 0;
	virtual std::shared_ptr<CMover_ShotBase> WeakShot(double baseATK, CVector position, float angle) = 0;

	double getMaxSpeed();
	double getAccelaration();

	double getAnimSpeed();
	int getShotRate();
	int getMaxCharge();

	int getStrongShotDuration();
};

